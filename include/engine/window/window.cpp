#include <engine/window/window.hpp>
#include <engine/device_data.hpp>
#include <engine/helper_functions.hpp>

#include <array>
#include <stdexcept>

// shamelessly stolen goods
double myClamp(double d, double min, double max) {
	const double t = d < min ? min : d;
	return t > max ? max : t;
}

void Window::init_window(const char* window_name, int window_width, int window_height) {
	const char* _windowName;
	int _windowHeight;
	int _windowWidth;

	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	_window = glfwCreateWindow(window_width, window_height, window_name, nullptr, nullptr);

	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::create_surface(VkInstance instance) {
	if (glfwCreateWindowSurface(instance, _window, nullptr, &_surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}

void Window::cleanup() {
	glfwDestroyWindow(_window);

	glfwTerminate();
}

VkExtent2D Window::choose_swap_extent(const VkSurfaceCapabilitiesKHR& capabilities) {
	if (capabilities.currentExtent.width != UINT32_MAX) {
		return capabilities.currentExtent;
	} else {
		int width, height;
		glfwGetFramebufferSize(_window, &width, &height);

		VkExtent2D actualExtent = {
			static_cast<uint32_t>(width),
			static_cast<uint32_t>(height)
		};

		actualExtent.width = myClamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
		actualExtent.height = myClamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

		return actualExtent;
	}
}

void Window::create_image_views() {
	// * Create swapchain image views
	_swapChainImageViews.resize(_swapChainImages.size());

	for (size_t i = 0; i < _swapChainImages.size(); i++) {
		VkImageViewCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image = _swapChainImages[i];
			createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			createInfo.format = _swapChainImageFormat;
			createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.baseMipLevel = 0;
			createInfo.subresourceRange.levelCount = 1;
			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.layerCount = 1;

		if (vkCreateImageView(_device, &createInfo, nullptr, &_swapChainImageViews[i]) != VK_SUCCESS) {
			throw std::runtime_error("failed to create image views!");
		}
	}

	// * Create shadowmap image
	create_image(_swapChainExtent.width,
					 _swapChainExtent.height,
					 1,
					 VK_FORMAT_D32_SFLOAT,
					 VK_IMAGE_TILING_OPTIMAL,
					 VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
					 VK_IMAGE_ASPECT_DEPTH_BIT,
					 _shadowMapImage,
					 _shadowMapImageMemory);

	// * ShadowMap image view creation
	VkImageViewCreateInfo view_info = {};
		view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		view_info.pNext = NULL;
		view_info.image = _shadowMapImage;
		view_info.format = VK_FORMAT_D32_SFLOAT;
		view_info.components.r = VK_COMPONENT_SWIZZLE_R;
		view_info.components.g = VK_COMPONENT_SWIZZLE_G;
		view_info.components.b = VK_COMPONENT_SWIZZLE_B;
		view_info.components.a = VK_COMPONENT_SWIZZLE_A;
		view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
		view_info.subresourceRange.baseMipLevel = 0;
		view_info.subresourceRange.levelCount = 1;
		view_info.subresourceRange.baseArrayLayer = 0;
		view_info.subresourceRange.layerCount = 1;
		view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
		view_info.flags = 0;

	if (vkCreateImageView(_device, &view_info, VK_NULL_HANDLE, &_shadowMapImageView) != VK_SUCCESS) {
		throw std::runtime_error("failed to create shadowmap image view!");
	}
}

void Window::create_framebuffers(VkDevice device) {
	_swapchainFrameBuffers.resize(_swapChainImageViews.size());

	for (size_t i = 0; i < _swapChainImageViews.size(); i++) {
		std::array<VkImageView, 2> attachments = {
                _swapChainImageViews[i],
                _depthImageView
            };

            VkFramebufferCreateInfo framebufferInfo{};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = _renderPass;
            framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
            framebufferInfo.pAttachments = attachments.data();
            framebufferInfo.width = _swapChainExtent.width;
            framebufferInfo.height = _swapChainExtent.height;
            framebufferInfo.layers = 1;

		if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &_swapchainFrameBuffers[i]) != VK_SUCCESS) {
			throw std::runtime_error("failed to create framebuffer!");
		}
	}
}

void Window::create_offscreen_framebuffer() {
	VkFramebufferCreateInfo fb_info;
		fb_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		fb_info.pNext = NULL;
		fb_info.renderPass = _shadowMappingRenderPass;
		fb_info.attachmentCount = 1;
		fb_info.pAttachments = &_shadowMapImageView;
		fb_info.width = _swapChainExtent.width;
		fb_info.height = _swapChainExtent.height;
		fb_info.layers = 1;
		fb_info.flags = 0;

	if (vkCreateFramebuffer(_device, &fb_info, NULL, &shadow_map_fb) != VK_SUCCESS) {
		throw std::runtime_error("failed to create shadow mapping framebuffer!");
	}
}

void Window::create_renderpass() {
	VkAttachmentDescription colorAttachment{};
		colorAttachment.format = _swapChainImageFormat;
		colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentDescription depthAttachment{};
		depthAttachment.format = find_depth_format();
		depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	VkAttachmentReference colorAttachmentRef{};
		colorAttachmentRef.attachment = 0;
		colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkAttachmentReference depthAttachmentRef{};
		depthAttachmentRef.attachment = 1;
		depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass{};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &colorAttachmentRef;
		subpass.pDepthStencilAttachment = &depthAttachmentRef;

	VkSubpassDependency dependency{};
		dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		dependency.dstSubpass = 0;
		dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		dependency.srcAccessMask = 0;
		dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

	std::array<VkAttachmentDescription, 2> attachments = {colorAttachment, depthAttachment};
	VkRenderPassCreateInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
		renderPassInfo.pAttachments = attachments.data();
		renderPassInfo.subpassCount = 1;
		renderPassInfo.pSubpasses = &subpass;
		renderPassInfo.dependencyCount = 1;
		renderPassInfo.pDependencies = &dependency;

	if (vkCreateRenderPass(_device, &renderPassInfo, nullptr, &_renderPass) != VK_SUCCESS) {
		throw std::runtime_error("failed to create render pass!");
	}
}

void Window::create_offscreen_renderpass() {
	VkAttachmentDescription attachments[2];
		// Depth attachment (shadow map)
		attachments[0].format = VK_FORMAT_D32_SFLOAT;
		attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
		attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		attachments[0].finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		attachments[0].flags = 0;

   // Attachment references from subpasses
   VkAttachmentReference depth_ref;
		depth_ref.attachment = 0;
		depth_ref.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

   // Subpass 0: shadow map rendering
   VkSubpassDescription subpass[1];
		subpass[0].pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass[0].flags = 0;
		subpass[0].inputAttachmentCount = 0;
		subpass[0].pInputAttachments = NULL;
		subpass[0].colorAttachmentCount = 0;
		subpass[0].pColorAttachments = NULL;
		subpass[0].pResolveAttachments = NULL;
		subpass[0].pDepthStencilAttachment = &depth_ref;
		subpass[0].preserveAttachmentCount = 0;
		subpass[0].pPreserveAttachments = NULL;

   // Create render pass
   VkRenderPassCreateInfo rp_info;
		rp_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		rp_info.pNext = NULL;
		rp_info.attachmentCount = 1;
		rp_info.pAttachments = attachments;
		rp_info.subpassCount = 1;
		rp_info.pSubpasses = subpass;
		rp_info.dependencyCount = 0;
		rp_info.pDependencies = NULL;
		rp_info.flags = 0;

   if (vkCreateRenderPass(_device, &rp_info, NULL, &_shadowMappingRenderPass) != VK_SUCCESS) {
		throw std::runtime_error("failed to create shadow mapping pass!");
	}
}

void Window::create_depth_resources() {
	VkFormat depthFormat = find_depth_format();

	create_image(_swapChainExtent.width, _swapChainExtent.height, 1, depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _depthImage, _depthImageMemory);
	_depthImageView = create_image_view(_depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT, 1);
}

void Window::cleanup_depth_image(){
	vkDestroyImageView(_device, _depthImageView, nullptr);
	vkDestroyImage(_device, _depthImage, nullptr);
	vkFreeMemory(_device, _depthImageMemory, nullptr);

	vkDestroyImageView(_device, _shadowMapImageView, nullptr);
	vkDestroyImage(_device, _shadowMapImage, nullptr);
	vkFreeMemory(_device, _shadowMapImageMemory, nullptr);
}
