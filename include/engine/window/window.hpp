#define GLFW_INCLUDE_VULKAN
#pragma once

#include <GLFW/glfw3.h>
#include <device/device.hpp>

#include <string>

// * Debugging
#include <iostream>

class Window {
public:
	GLFWwindow* _window;
	VkSurfaceKHR _surface;
	VkSwapchainKHR _swapChain;
	VkExtent2D _swapChainExtent;
	VkFormat _swapChainImageFormat;
	std::vector<VkImage> _swapChainImages;
	std::vector<VkImageView> _swapChainImageViews;
	std::vector<VkFramebuffer> _swapchainFrameBuffers;
	VkRenderPass _renderPass;

	VkImage _depthImage;
	VkDeviceMemory _depthImageMemory;
	VkImageView _depthImageView;

	// * Shadow mapping
	VkRenderPass _shadowMappingRenderPass;
	VkFramebuffer shadow_map_fb;

	VkImageView 	_shadowMapImageView;
	VkImage			_shadowMapImage;
	VkDeviceMemory _shadowMapImageMemory;

	void init_window(const char* window_name, int window_width, int window_height);
	void create_surface(VkInstance instance);
	VkExtent2D choose_swap_extent(const VkSurfaceCapabilitiesKHR& capabilities);
	void create_image_views();

	void create_framebuffers(VkDevice device);
	void create_offscreen_framebuffer();

	void create_renderpass();
	void create_offscreen_renderpass();

	void create_depth_resources();
	void cleanup();
	void cleanup_depth_image();

private:
	const char* _windowName;
	int _windowHeight;
	int _windowWidth;

	struct FrameBufferAttachment {
		VkImage image;
		VkDeviceMemory mem;
		VkImageView view;
	};

	struct OffScreenPass {
		int32_t width, height;
		VkFramebuffer frameBuffer;
		FrameBufferAttachment depth;
		VkRenderPass renderPass;
		VkSampler depthSampler;
		VkDescriptorImageInfo descriptor;
	} offscreenPass;
};
