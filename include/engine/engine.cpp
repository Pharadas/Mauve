#include <engine/engine.hpp>
#include <engine/buffer_helper.hpp>
#include <engine/helper_functions.hpp>

#define MAX_VERTICES 64000;

void Engine::init(std::vector<std::string> texturePaths) {
	_engineWindow.init_window("Vulkan Gamin", 800, 600);
	glfwSetWindowUserPointer(_engineWindow._window, this);
	glfwSetFramebufferSizeCallback(_engineWindow._window, framebufferResizeCallback);
	init_vulkan();

	init_textures(texturePaths);
	init_materials();
	// init_scene();
	// main_loop();
	// cleanup();
}

void Engine::render() {
	// * Calculos para fps
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	fractionsOfSecondPassed += deltaTime;
	framesPassed++;
	sumFps += 1. / deltaTime;
	numFps++;
	std::cout << "fps: " << 1 / deltaTime << "             " << '\r';
	if (fractionsOfSecondPassed > 1.) {
		std::cout << "fps: " << framesPassed << "      \r";
		fractionsOfSecondPassed = 0;
		framesPassed = 0;
	}

	if (glfwWindowShouldClose(_engineWindow._window))
		running = false;

	process_input();

	glfwPollEvents();
	// update_materials();
	draw_frame();
	worldObjectsToDraw		  .clear();
	texturedWorldObjectsToDraw.clear();
	pointsWorldObjectsToDraw  .clear();
}

void Engine::draw(WorldObject objeto) {
	worldObjectsToDraw.push_back(objeto);
}

void Engine::draw(TexturedWorldObject objeto) {
	texturedWorldObjectsToDraw.push_back(objeto);
}

void Engine::draw(PointsWorldObject objeto) {
	pointsWorldObjectsToDraw.push_back(objeto);
}

void Engine::uploadMeshToEngine(std::shared_ptr<Mesh> meshPtr, bool autoIndex) {
	// * Asignar memoria este mesh
	meshPtr->build(_commandPool, _engineDevice._graphicsQueue, autoIndex);
	meshesList.push_back(meshPtr);
}

void Engine::uploadMaterialToEngine(std::shared_ptr<Material> materialPtr) {
	// * Asignar memoria este mesh
	materialPtr->build(_engineWindow._renderPass, _engineWindow._swapChainExtent, global_projection_buffer);
}

void Engine::init_vulkan() {
	create_instance();
	setup_debug_messenger();
	_engineWindow.create_surface(_instance);
	_engineDevice.pick_physical_device(_instance, _engineWindow._surface);
	_engineDevice.create_logical_device(_enableValidationLayers, _validationLayers);
	create_swapchain();
	_engineWindow.create_image_views();
	_engineWindow.create_renderpass();

	create_command_pool();
	_engineWindow.create_depth_resources();
	_engineWindow.create_framebuffers(_device);

	create_texture_sampler();

	create_global_projection_buffers();
	create_command_buffers();
	create_sync_objects();
}

void Engine::init_scene() {
	// init_textures();
	// init_materials();
	// init_meshes();
	// init_world();

	// worldObjectsMap.insert(std::make_pair("icosahedron_light", new TexturedWorldObject(meshesMap["icosahedron"], materialsMap["textured"], 0)));
}

// void Engine::main_loop() {
// 	Chunk thisChunk(glm::vec2(0, 0), perlin, _commandPool, _engineDevice._graphicsQueue, materialsMap["textured"]);

// 	while (!glfwWindowShouldClose(_engineWindow._window)) {
		

// 		// worldObjectsToDraw.push_back(worldObjectsMap["worldCube"]);
// 		worldObjectsToDraw.push_back(thisChunk.chunkRenderableObject.get());
// 		// objectsToDraw.push_back(worldObjectsMap["icosahedron_light"]);
// 		// // objectsToDraw.push_back(worldObjectsMap["icosahedron_space"]);
// 		// objectsToDraw.push_back(worldObjectsMap["icosahedron_videoman_lit"]);
// 		// worldObjectsMap["icosahedron_videoman_lit"]->rotation += 1;
// 	}

// 	vkDeviceWaitIdle(_device);
// }

void Engine::cleanup() {
	std::cout << "ave fps = " << sumFps / numFps << '\n';
	vkDestroyBuffer(_device, global_projection_buffer, nullptr);
	vkDestroyBuffer(_device, global_lighting_info_buffer, nullptr);
	vkFreeMemory(_device, global_projection_buffer_memory, nullptr);
	vkFreeMemory(_device, global_lighting_info_buffer_memory, nullptr);

	cleanup_swapchain();

	defaultMaterial.get()->cleanup();
	texturedMaterial.get()->cleanup();
	pointsMaterial.get()->cleanup();

	// for (auto mesh : meshesMap) {
	// 	mesh.second->cleanup();
	// }

	for (auto mesh : meshesList) {
		mesh.get()->cleanup();
	}

	for (auto texture : texturesVector) {
		texture.cleanup();
	}

	// for (auto tex : texturesVector) {
	// 	tex.cleanup();
	// }

	// for (auto worldObject : worldObjectsMap) {
	// 	worldObject.second->cleanup();
	// }

	_engineWindow.cleanup_depth_image();
	vkDestroySampler(_device, _textureSampler, nullptr);

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		vkDestroySemaphore(_device, _renderFinishedSemaphores[i], nullptr);
		vkDestroySemaphore(_device, _imageAvailableSemaphores[i], nullptr);
		vkDestroyFence(_device, _inFlightFences[i], nullptr);
	}

	vkDestroyCommandPool(_device, _commandPool, nullptr);

	vkDestroyDevice(_device, nullptr);

	if (_enableValidationLayers) {
		destroy_debug_utils_messenger_EXT(_instance, _debugMessenger, nullptr);
	}

	vkDestroySurfaceKHR(_instance, _engineWindow._surface, nullptr);
	vkDestroyInstance(_instance, nullptr);

	_engineWindow.cleanup();
}

void Engine::create_instance() {
	if (_enableValidationLayers && !check_validation_layer_support()) {
		throw std::runtime_error("validation layers requested, but not available!");
	}

	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Hello Triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_2;

	VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

	auto extensions = getRequiredExtensions();
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();

	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
	if (_enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(_validationLayers.size());
		createInfo.ppEnabledLayerNames = _validationLayers.data();

		populate_debug_messenger_create_info(debugCreateInfo);
		createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
	} else {
		createInfo.enabledLayerCount = 0;

		createInfo.pNext = nullptr;
	}

	if (vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS) {
		throw std::runtime_error("failed to create instance!");
	}
}

// validation layers debugging
VkResult Engine::create_debug_utils_messenger_EXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void Engine::destroy_debug_utils_messenger_EXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}

void Engine::populate_debug_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
	createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		// VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
		createInfo.messageSeverity =  VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		createInfo.pfnUserCallback = debug_callback;
}

void Engine::setup_debug_messenger() {
	if (!_enableValidationLayers) return;

	VkDebugUtilsMessengerCreateInfoEXT createInfo;
	populate_debug_messenger_create_info(createInfo);

	if (create_debug_utils_messenger_EXT(_instance, &createInfo, nullptr, &_debugMessenger) != VK_SUCCESS) {
		throw std::runtime_error("failed to set up debug messenger!");
	}
}

std::vector<const char*> Engine::getRequiredExtensions() {
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (_enableValidationLayers) {
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return extensions;
}

bool Engine::check_validation_layer_support() {
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : _validationLayers) {
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers) {
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}

		if (!layerFound) {
			return false;
		}
	}

	return true;
}

VKAPI_ATTR VkBool32 VKAPI_CALL Engine::debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
	std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

	return VK_FALSE;
}

void Engine::create_swapchain() {
	SwapChainSupportDetails swapChainSupport = _engineDevice.query_swap_chain_support(_physicalDevice);
	VkSurfaceFormatKHR surfaceFormat = _engineDevice.choose_swap_surface_format(swapChainSupport.formats);
	VkPresentModeKHR presentMode = _engineDevice.choose_swap_present_mode(swapChainSupport.presentModes);
	VkExtent2D extent = _engineWindow.choose_swap_extent(swapChainSupport.capabilities);

	uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
	if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
		imageCount = swapChainSupport.capabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = _engineWindow._surface;

		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	QueueFamilyIndices indices = _engineDevice.find_queue_families(_physicalDevice);
	uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

	if (indices.graphicsFamily != indices.presentFamily) {
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	} else {
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	}

	createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = presentMode;
	createInfo.clipped = VK_TRUE;

	createInfo.oldSwapchain = VK_NULL_HANDLE;

	if (vkCreateSwapchainKHR(_device, &createInfo, nullptr, &_engineWindow._swapChain) != VK_SUCCESS) {
		throw std::runtime_error("failed to create swap chain!");
	}

	vkGetSwapchainImagesKHR(_device, _engineWindow._swapChain, &imageCount, nullptr);
	_engineWindow._swapChainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(_device, _engineWindow._swapChain, &imageCount, _engineWindow._swapChainImages.data());

	_engineWindow._swapChainImageFormat = surfaceFormat.format;
	_engineWindow._swapChainExtent = extent;

	proj = glm::perspective(glm::radians(90.f), (float) _engineWindow._swapChainExtent.width / (float) _engineWindow._swapChainExtent.height, 0.001f, 1000.0f);
	proj[1][1] *= -1;
}

void Engine::create_command_pool() {
	QueueFamilyIndices queueFamilyIndices = _engineDevice.find_queue_families(_physicalDevice);

	VkCommandPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

	if (vkCreateCommandPool(_device, &poolInfo, nullptr, &_commandPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create command pool!");
	}
}

void Engine::create_command_buffers() {
	commandBuffers;
	commandBuffers.resize(_engineWindow._swapchainFrameBuffers.size());

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = _commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t) commandBuffers.size();

	if (vkAllocateCommandBuffers(_device, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate command buffers!");
	}
}

void Engine::draw_frame() {
	vkWaitForFences(_device, 1, &_inFlightFences[_currentFrame], VK_TRUE, UINT64_MAX);

	uint32_t imageIndex;
	VkResult result = vkAcquireNextImageKHR(_device, _engineWindow._swapChain, UINT64_MAX, _imageAvailableSemaphores[_currentFrame], VK_NULL_HANDLE, &imageIndex);

	if (result == VK_ERROR_OUT_OF_DATE_KHR) {
		recreate_swapchain();
		return;
	} else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
		throw std::runtime_error("failed to acquire swap chain image!");
	}

	if (_imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
		vkWaitForFences(_device, 1, &_imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
	}
	_imagesInFlight[imageIndex] = _inFlightFences[_currentFrame];

	// setup submit info for VkQueueSubmit
	VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = {_imageAvailableSemaphores[_currentFrame]};
	VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;

		// * en un solo command buffer voy a grabar todos los commandos de vkdraw
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffers[imageIndex]; // para decirle a vkqueuesubmit cual buffer usar ahora (porque se ciclan cada frame)

	VkSemaphore signalSemaphores[] = {_renderFinishedSemaphores[_currentFrame]};
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;

	vkResetFences(_device, 1, &_inFlightFences[_currentFrame]);

	// setup command buffer to record on this frame
	VkCommandBufferBeginInfo bufferBeginInfo{};
		bufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		bufferBeginInfo.pNext = nullptr;
		bufferBeginInfo.pInheritanceInfo = nullptr;
		bufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(commandBuffers[imageIndex], &bufferBeginInfo);

	VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = _engineWindow._renderPass;
		renderPassInfo.framebuffer = _engineWindow._swapchainFrameBuffers[imageIndex];
		renderPassInfo.renderArea.offset = {0, 0};
		renderPassInfo.renderArea.extent = _engineWindow._swapChainExtent;

		std::array<VkClearValue, 2> clearValues{};
			clearValues[0].color = {{0.0f, 0.0f, 0.0f, 1.0f}};
			clearValues[1].depthStencil = {1.0f, 0};

		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();

	// now we begin the renderpass so that we can record commands to the command buffer
	vkCmdBeginRenderPass(commandBuffers[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		// * Actualizar el buffer global de los WorldObjects
		glm::mat4 view = _camera.GetViewMatrix();

		VP globalVPBuffer;
			globalVPBuffer.proj = proj;
			globalVPBuffer.view = view;

		MeshPushConstants meshConstants;

		// glm::mat4 objectsViewMatrices[MAX_OBJECTS] = {};
		// LightingInfo lightingInfoForBuffer[MAX_OBJECTS] 		  = {};

		// for (int i = 0; i < worldObjectsToDraw.size(); i++) {
		// 	// * Llenar el buffer de GlobalProjectionInfo
		// 	glm::mat4 model{1.f};
		// 		model = glm::rotate(model, glm::radians(worldObjectsToDraw[i].rotation), glm::vec3(1, 1, 1));
		// 		model = glm::scale(model, worldObjectsToDraw[i].scale);
		// 		model = glm::translate(model, worldObjectsToDraw[i].position);
		// 		meshConstants.modelMatrix = model; // * Por ahora lo dejo solo por la alineacion, me da flojera moverle xd

		// 	// GlobalProjectionInfo gpi = {};
		// 	// 	gpi.model = model;
		// 	// 	gpi.proj = proj;
		// 	// 	gpi.view = view;

		// 	// objectsViewMatrices[i] = model;

		// 	// // * Llenar el buffer de LightingInfo
		// 	// LightingInfo li = {};
		// 	// 	li.viewPos = _camera.Position;
		// 	// 	li.objectColor = worldObjectsToDraw[i].color;
		// 	// 	li.lightPos = worldObjectsMap["icosahedron_light"]->position;
		// 	// 	li.lightColor = glm::vec3(1, 1, 1);

		// 	// lightingInfoForBuffer[i] = li;
		// }

		// for (int i = 0; i < texturedWorldObjectsToDraw.size(); i++) {
		// 	// * Llenar el buffer de GlobalProjectionInfo
		// 	glm::mat4 model{1.f};
		// 		model = glm::rotate(model, glm::radians(texturedWorldObjectsToDraw[i].rotation), glm::vec3(1, 1, 1));
		// 		model = glm::scale(model, texturedWorldObjectsToDraw[i].scale);
		// 		model = glm::translate(model, texturedWorldObjectsToDraw[i].position);
		// 		meshConstants.modelMatrix = model; // * Por ahora lo dejo solo por la alineacion, me da flojera moverle xd

		// 	// GlobalProjectionInfo gpi = {};
		// 	// 	gpi.model = model;
		// 	// 	gpi.proj = proj;
		// 	// 	gpi.view = view;

		// 	// objectsProjectionsForBuffer[i + worldObjectsToDraw.size()] = gpi;
		// }

		void* data;
		// * Agregar los valores de proyeccion de view y proj
		vkMapMemory(_device, global_projection_buffer_memory, 0, sizeof(VP), 0, &data);
			memcpy(data, &globalVPBuffer, sizeof(VP));
		vkUnmapMemory(_device, global_projection_buffer_memory);

		// // * Agregar los valores de proyeccion de este objeto al buffer de proyeccion global
		// vkMapMemory(_device, global_lighting_info_buffer_memory, 0, sizeof(LightingInfo) * MAX_OBJECTS, 0, &data);
		// 	memcpy(data, &lightingInfoForBuffer, sizeof(LightingInfo) * MAX_OBJECTS);
		// vkUnmapMemory(_device, global_lighting_info_buffer_memory);

		// * Lo voy a hacer hard-coded por ahora
			vkCmdBindPipeline(commandBuffers[imageIndex], VK_PIPELINE_BIND_POINT_GRAPHICS, defaultMaterial.get()->pipeline);
			defaultMaterial.get()->setup_descriptor_set(commandBuffers[imageIndex]);
			for (int i = 0; i < worldObjectsToDraw.size(); i++) {
				worldObjectsToDraw[i].draw(commandBuffers[imageIndex], i, meshConstants);
			}

			vkCmdBindPipeline(commandBuffers[imageIndex], VK_PIPELINE_BIND_POINT_GRAPHICS, texturedMaterial.get()->pipeline);
			texturedMaterial.get()->setup_descriptor_set(commandBuffers[imageIndex]);
			for (int i = 0; i < texturedWorldObjectsToDraw.size(); i++) {
				texturedWorldObjectsToDraw[i].draw(commandBuffers[imageIndex], i + worldObjectsToDraw.size(), meshConstants);
			}

			vkCmdBindPipeline(commandBuffers[imageIndex], VK_PIPELINE_BIND_POINT_GRAPHICS, pointsMaterial.get()->pipeline);
			pointsMaterial.get()->setup_descriptor_set(commandBuffers[imageIndex]);
			for (int i = 0; i < pointsWorldObjectsToDraw.size(); i++) {
				pointsWorldObjectsToDraw[i].draw(commandBuffers[imageIndex], i + worldObjectsToDraw.size() + texturedWorldObjectsToDraw.size(), meshConstants);
			}

		defaultMaterial .get()->currObject = 0;
		texturedMaterial.get()->currObject = 0;
		pointsMaterial	 .get()->currObject = 0;

		// for (auto material : materialsMap) {
		// 	material.second->currObject = 0;
		// }

	vkCmdEndRenderPass(commandBuffers[imageIndex]);
	vkEndCommandBuffer(commandBuffers[imageIndex]);

	if (vkQueueSubmit(_engineDevice._graphicsQueue, 1, &submitInfo, _inFlightFences[_currentFrame]) != VK_SUCCESS) {
		throw std::runtime_error("failed to submit draw command buffer!");
	}

	VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = {_engineWindow._swapChain};
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;

		presentInfo.pImageIndices = &imageIndex;

	result = vkQueuePresentKHR(_engineDevice._presentQueue, &presentInfo); // aqui mete la imagen creada al queue para presentarla cuando pueda

	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || _frameBuffer_resized) { // checar si cambio el tamano de la pantalla, si si, recrear la swapchain
		_frameBuffer_resized = false;
		recreate_swapchain();
	} else if (result != VK_SUCCESS) {
		throw std::runtime_error("failed to present swap chain image!");
	}

	_currentFrame = (_currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void Engine::create_sync_objects() {
	_imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	_renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	_inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
	_imagesInFlight.resize(_engineWindow._swapChainImages.size(), VK_NULL_HANDLE);

	VkSemaphoreCreateInfo semaphoreInfo{};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VkFenceCreateInfo fenceInfo{};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		if (vkCreateSemaphore(_device, &semaphoreInfo, nullptr, &_imageAvailableSemaphores[i]) != VK_SUCCESS ||
			vkCreateSemaphore(_device, &semaphoreInfo, nullptr, &_renderFinishedSemaphores[i]) != VK_SUCCESS ||
			vkCreateFence(_device, &fenceInfo, nullptr, &_inFlightFences[i]) != VK_SUCCESS) {
			throw std::runtime_error("failed to create synchronization objects for a frame!");
		}
	}
}

// esta funcion solo se deberia llamar cuando se cambie de tamano de pantalla
void Engine::recreate_swapchain() {
	// TODO Esta funcion deja sin destruir 2 VkImage's, VkDeviceMemory's y VkImageView's
	int width = 0, height = 0;
	glfwGetFramebufferSize(_engineWindow._window, &width, &height);
	while (width == 0 || height == 0) {
		glfwGetFramebufferSize(_engineWindow._window, &width, &height);
		glfwWaitEvents();
	}

	vkDeviceWaitIdle(_device);

	cleanup_swapchain();
	_engineWindow.cleanup_depth_image();

	// call cleanup functions on all material objects

	create_swapchain();
	_engineWindow.create_image_views();
	_engineWindow.create_renderpass();

	_engineWindow.create_depth_resources();

	_engineWindow.create_framebuffers(_device);
	create_command_buffers();

	defaultMaterial.get()->recreate(_engineWindow._renderPass, _engineWindow._swapChainExtent);
	texturedMaterial.get()->recreate(_engineWindow._renderPass, _engineWindow._swapChainExtent);
	pointsMaterial.get()->recreate(_engineWindow._renderPass, _engineWindow._swapChainExtent);

	// // * clear all materials
	// // materialsMap.clear();
	// std::cout << "rebuilding materials\n";

	// // * Recreate materials
	// for (auto material : materialsMap) {
	// 	material.second->recreate(_engineWindow._renderPass, _engineWindow._swapChainExtent);
	// }

	_imagesInFlight.resize(_engineWindow._swapChainImages.size(), VK_NULL_HANDLE);
}

void Engine::cleanup_swapchain() {
	for (size_t i = 0; i < _engineWindow._swapchainFrameBuffers.size(); i++) {
        vkDestroyFramebuffer(_device, _engineWindow._swapchainFrameBuffers[i], nullptr);
    }

    vkFreeCommandBuffers(_device, _commandPool, static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());

    vkDestroyRenderPass(_device, _engineWindow._renderPass, nullptr);

    for (size_t i = 0; i < _engineWindow._swapChainImageViews.size(); i++) {
        vkDestroyImageView(_device, _engineWindow._swapChainImageViews[i], nullptr);
    }

    vkDestroySwapchainKHR(_device, _engineWindow._swapChain, nullptr);
}

void Engine::create_texture_sampler() {
	VkPhysicalDeviceProperties properties{};
	vkGetPhysicalDeviceProperties(_physicalDevice, &properties);

	VkSamplerCreateInfo samplerInfo{};
		samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		// samplerInfo.magFilter = VK_FILTER_LINEAR;
		// samplerInfo.minFilter = VK_FILTER_LINEAR;

		samplerInfo.magFilter = VK_FILTER_NEAREST;
		samplerInfo.minFilter = VK_FILTER_NEAREST;

		// samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		// samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		// samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;

		samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
		samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
		samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;

		samplerInfo.anisotropyEnable = VK_TRUE;
		samplerInfo.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
		samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
		samplerInfo.unnormalizedCoordinates = VK_FALSE;
		samplerInfo.compareEnable = VK_FALSE;
		samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;

		samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
		samplerInfo.minLod = .0;
		samplerInfo.maxLod = static_cast<float>(16);
		samplerInfo.mipLodBias = .0;

	if (vkCreateSampler(_device, &samplerInfo, nullptr, &_textureSampler) != VK_SUCCESS) {
		throw std::runtime_error("failed to create texture sampler!");
	}
}

void Engine::process_input() {
	GLdouble xPos, yPos;
	glfwGetCursorPos(_engineWindow._window, &xPos, &yPos);

	_camera.ProcessMouseMovement(xPos, yPos);

	if (glfwGetKey(_engineWindow._window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(_engineWindow._window, true);

	// para no volar, solo multiplicar la velocidad (de deltatime) con el _camera front X y Z pero dejando Y en 0
	if (glfwGetKey(_engineWindow._window, GLFW_KEY_W) == GLFW_PRESS)
		_camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(_engineWindow._window, GLFW_KEY_S) == GLFW_PRESS)
		_camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(_engineWindow._window, GLFW_KEY_A) == GLFW_PRESS)
		_camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(_engineWindow._window, GLFW_KEY_D) == GLFW_PRESS)
		_camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(_engineWindow._window, GLFW_KEY_E) == GLFW_PRESS)
		_camera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(_engineWindow._window, GLFW_KEY_Q) == GLFW_PRESS)
		_camera.ProcessKeyboard(DOWN, deltaTime);
}

void Engine::create_vertex_buffer() {
	VkDeviceSize bufferSize = sizeof(Vertex) * MAX_VERTICES;

	create_buffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, global_vertex_buffer, global_vertex_buffer_memory);
}

void Engine::add_texture(std::string textureName, const char* texturePath) {
	texturesNumsMap[textureName] = texturesVector.size();
	texturesVector.push_back(Texture(texturePath, _commandPool, _engineDevice._graphicsQueue));
}

void Engine::init_textures(std::vector<std::string> texturePaths) {
	for (auto name : texturePaths) {
		// * Inicializar aqui todas  last texturas
		add_texture(name, ("textures/" + name + ".jpg").c_str());
	}
	std::cout << "numero de texturas: " << texturesVector.size() << '\n';
}

void Engine::init_materials() {
	defaultMaterial = std::make_shared<Material>();
	uploadMaterialToEngine(defaultMaterial);

	texturedMaterial = std::make_shared<Textured_Material>(texturesVector, &_textureSampler);
	uploadMaterialToEngine(texturedMaterial);

	pointsMaterial = std::make_shared<Points_Material>();
	uploadMaterialToEngine(pointsMaterial);
}

void Engine::init_meshes() {
	std::vector<Vertex> vertices = {
		{{-1, -1,  1}, {1, 0, 1}, {0, 1}}, // 0
		{{ 1, -1,  1}, {1, 0, 1}, {1, 1}}, // 1
		{{-1,  1,  1}, {1, 0, 1}, {0, 0}}, // 2
		{{ 1,  1,  1}, {1, 0, 1}, {1, 0}}, // 3
		{{ 1, -1,  1}, {1, 0, 1}, {0, 1}}, // 4
		{{ 1, -1, -1}, {1, 0, 1}, {1, 1}}, // 5
		{{ 1,  1,  1}, {1, 0, 1}, {0, 0}}, // 6
		{{ 1,  1, -1}, {1, 0, 1}, {1, 0}}, // 7
		{{ 1, -1, -1}, {1, 0, 1}, {0, 1}}, // 8
		{{-1, -1, -1}, {1, 0, 1}, {1, 1}}, // 9
		{{ 1,  1, -1}, {1, 0, 1}, {0, 0}}, // 10
		{{-1,  1, -1}, {1, 0, 1}, {1, 0}}, // 11
		{{-1, -1, -1}, {1, 0, 1}, {0, 1}}, // 12
		{{-1, -1,  1}, {1, 0, 1}, {1, 1}}, // 13
		{{-1,  1, -1}, {1, 0, 1}, {0, 0}}, // 14
		{{-1,  1,  1}, {1, 0, 1}, {1, 0}}, // 15
		{{ 1,  1, -1}, {1, 0, 1}, {0, 1}}, // 16
		{{-1,  1, -1}, {1, 0, 1}, {1, 1}}, // 17
		{{ 1,  1,  1}, {1, 0, 1}, {0, 0}}, // 18
		{{-1,  1,  1}, {1, 0, 1}, {1, 0}}, // 19
		{{ 1, -1,  1}, {1, 0, 1}, {0, 1}}, // 20
		{{-1, -1,  1}, {1, 0, 1}, {1, 1}}, // 21
		{{ 1, -1, -1}, {1, 0, 1}, {0, 0}}, // 22
		{{-1, -1, -1}, {1, 0, 1}, {1, 0}}, // 23
	};
	std::vector<Vertex> icosahedron = {};
	std::vector<Vertex> cube = {};

	glm::vec3 list[] = {
		{-1.0f,-1.0f,-1.0f},
		{-1.0f,-1.0f, 1.0f},
		{-1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f,-1.0f},
		{-1.0f,-1.0f,-1.0f},
		{-1.0f, 1.0f,-1.0f},
		{1.0f,-1.0f, 1.0f},
		{-1.0f,-1.0f,-1.0f},
		{1.0f,-1.0f,-1.0f},
		{1.0f, 1.0f,-1.0f},
		{1.0f,-1.0f,-1.0f},
		{-1.0f,-1.0f,-1.0f},
		{-1.0f,-1.0f,-1.0f},
		{-1.0f, 1.0f, 1.0f},
		{-1.0f, 1.0f,-1.0f},
		{1.0f,-1.0f, 1.0f},
		{-1.0f,-1.0f, 1.0f},
		{-1.0f,-1.0f,-1.0f},
		{-1.0f, 1.0f, 1.0f},
		{-1.0f,-1.0f, 1.0f},
		{1.0f,-1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
		{1.0f,-1.0f,-1.0f},
		{1.0f, 1.0f,-1.0f},
		{1.0f,-1.0f,-1.0f},
		{1.0f, 1.0f, 1.0f},
		{1.0f,-1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f,-1.0f},
		{-1.0f, 1.0f,-1.0f},
		{1.0f, 1.0f, 1.0f},
		{-1.0f, 1.0f,-1.0f},
		{-1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
		{-1.0f, 1.0f, 1.0f},
		{1.0f,-1.0f, 1.0},
	};

	// for (int i = 0; i < 36; i += 3) {
	// 	addTriangle(list[i], list[i + 1], list[i + 2], cube);
	// }

	// cube.push_back({{-1.0f,-1.0f,-1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{-1.0f,-1.0f, 1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{-1.0f, 1.0f, 1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{1.0f, 1.0f,-1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{-1.0f,-1.0f,-1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{-1.0f, 1.0f,-1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{1.0f,-1.0f, 1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{-1.0f,-1.0f,-1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{1.0f,-1.0f,-1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{1.0f, 1.0f,-1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{1.0f,-1.0f,-1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{-1.0f,-1.0f,-1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{-1.0f,-1.0f,-1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{-1.0f, 1.0f, 1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{-1.0f, 1.0f,-1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{1.0f,-1.0f, 1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{-1.0f,-1.0f, 1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{-1.0f,-1.0f,-1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{-1.0f, 1.0f, 1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{-1.0f,-1.0f, 1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{1.0f,-1.0f, 1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{1.0f, 1.0f, 1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{1.0f,-1.0f,-1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{1.0f, 1.0f,-1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{1.0f,-1.0f,-1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{1.0f, 1.0f, 1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{1.0f,-1.0f, 1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{1.0f, 1.0f, 1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{1.0f, 1.0f,-1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{-1.0f, 1.0f,-1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{1.0f, 1.0f, 1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{-1.0f, 1.0f,-1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{-1.0f, 1.0f, 1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{1.0f, 1.0f, 1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{-1.0f, 1.0f, 1.0f}, {1., 1., 1.}, {1, 0}});
	// cube.push_back({{1.0f,-1.0f, 1.0f}, {1., 1., 1.}, {1, 0}});

	// meshesMap.insert(std::make_pair("cube", new Mesh(vertices, _commandPool, _engineDevice._graphicsQueue)));
	// meshesMap.insert(std::make_pair("icosahedron", new Mesh(icosahedron, _commandPool, _engineDevice._graphicsQueue)));
	// meshesMap.insert(std::make_pair("cube", 		  new Mesh(cube, 			_commandPool, _engineDevice._graphicsQueue)));
}

// * Actualiza la informacion que es independiente del world object
void Engine::update_materials() {
	// dynamic_cast<Textured_Lit_Material&>(*materialsMap["textured_lit"]).lightInfo.lightPos = (worldObjectsMap["icosahedron_light"])->position;
	// dynamic_cast<Textured_Lit_Material&>(*materialsMap["textured_lit"]).lightInfo.viewPos = _camera.Position;
}

void Engine::create_global_projection_buffers() {
	create_buffer(sizeof(VP), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, global_projection_buffer, global_projection_buffer_memory);
	create_buffer(sizeof(LightingInfo), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, global_lighting_info_buffer, global_lighting_info_buffer_memory);
}

void Engine::init_world() {
}
