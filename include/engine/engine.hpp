#pragma once

#include <engine/window/window.hpp>
#include <engine/device/device.hpp>
#include <engine/pipeline/pipeline.hpp>
#include <engine/descriptors/descriptor.hpp>
#include <engine/texture/texture.hpp>
#include <camera.hpp>

#include <engine/device_data.hpp>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdexcept>
#include <vector>

class Engine {
public:
	bool _frameBuffer_resized = false;

	void run();

private:
	// private members
	VkInstance _instance;
	const std::vector<const char*> _validationLayers = {"VK_LAYER_KHRONOS_validation"};
	bool _enableValidationLayers = true;
	VkDebugUtilsMessengerEXT _debugMessenger;

	VkCommandPool _commandPool;
	std::vector<VkCommandBuffer> commandBuffers;

	VkSemaphore _imageAvailableSemaphore;
	VkSemaphore _renderFinishedSemaphore;
	const int MAX_FRAMES_IN_FLIGHT = 2;

	std::vector<VkSemaphore> _imageAvailableSemaphores;
	std::vector<VkSemaphore> _renderFinishedSemaphores;
	std::vector<VkFence> _inFlightFences;
	std::vector<VkFence> _imagesInFlight;
	size_t _currentFrame = 0;

	VkBuffer _vertexBuffer;
    VkDeviceMemory _vertexBufferMemory;
	VkBuffer _indexBuffer;
	VkDeviceMemory _indexBufferMemory;
	std::vector<VkBuffer> _uniformBuffers;
	std::vector<VkDeviceMemory> _uniformBuffersMemory;

	VkSampler _textureSampler;

	float deltaTime;
	float lastFrame;

	Window _engineWindow;
	Device _engineDevice;
	Pipeline _enginePipeline;
	Descriptors _engineDescriptors;
	Camera _camera;
	
	Texture _engineTexture;

	float rotation = 0.f;

	// private methods
	// init vulkan and main functions
	void init_vulkan();
	void main_loop();
	void cleanup();

	// initialization
	void create_instance();

	// extensions
	std::vector<const char*> getRequiredExtensions();

	// validation layers
	VkResult create_debug_utils_messenger_EXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
	void destroy_debug_utils_messenger_EXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
	void populate_debug_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	void setup_debug_messenger();
	bool check_validation_layer_support();
	static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

	// swapchain
	void create_swapchain();
	void recreate_swapchain();
	void cleanup_swapchain();

	// renderpass
	// void create_renderpass();

	// buffers
	void create_command_pool();
	void create_command_buffers();
	void create_vertex_buffer();
	void copy_buffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	void create_index_buffer();
	void create_uniform_buffers();

	void update_uniform_buffer(uint32_t currentImage);

	// drawing
	void draw_frame();
	void create_sync_objects();
	void create_semaphores();

	// texture setup
	void create_texture_sampler();

	void process_input();
};

static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
	auto engine = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window));
	engine->_frameBuffer_resized = true;
}
