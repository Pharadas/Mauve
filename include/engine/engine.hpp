#pragma once

#include <vulkan/vulkan.h>

#include <engine/window/window.hpp>
#include <engine/device/device.hpp>
#include <engine/texture/texture.hpp>
#include <engine/world_object/world_object.hpp>
#include <camera.hpp>
#include <tiny_obj_loader.h>

#include <engine/device_data.hpp>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <windows.h>
#include <string>
#include <limits.h>

#include <chrono>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdexcept>
#include <vector>
#include <map>
#include <memory>

class Engine {
public:
	bool _frameBuffer_resized = false;
	std::vector<WorldObject*> objectsToDraw;
	bool running = true;
	float deltaTime;
	std::shared_ptr<Material> defaultMaterial;
	std::shared_ptr<Textured_Material> texturedMaterial;

	void init();
	void draw();
	void uploadMeshToEngine(	 std::shared_ptr<Mesh> 		meshPtr);
	// * Por ahora solo existe para que en el futuro los usuarios puedan crear sus propios materiales
	void uploadMaterialToEngine(std::shared_ptr<Material> materialPtr);
	void cleanup();
	void end();

private:
	// private members
	VkInstance _instance;
	const std::vector<const char*> _validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

	bool _enableValidationLayers = true;

	VkDebugUtilsMessengerEXT _debugMessenger;

	float fractionsOfSecondPassed = 0;
	int framesPassed = 0;

	VkCommandPool _commandPool;
	std::vector<VkCommandBuffer> commandBuffers;

	VkSemaphore _imageAvailableSemaphore;
	VkSemaphore _renderFinishedSemaphore;
	const int MAX_FRAMES_IN_FLIGHT = 2;
	const int MAX_OBJECTS = 1000;

	std::vector<VkSemaphore> _imageAvailableSemaphores;
	std::vector<VkSemaphore> _renderFinishedSemaphores;
	std::vector<VkFence> _inFlightFences;
	std::vector<VkFence> _imagesInFlight;
	size_t _currentFrame = 0;

	VkDescriptorSet globalDescriptorSet;

	std::unordered_map<std::string, Mesh*> meshesMap;
	std::unordered_map<std::string, Material*> materialsMap;
	std::unordered_map<std::string, WorldObject*> worldObjectsMap;
	std::vector<std::string> texturesList;
	std::vector<Texture> texturesVector;

	VkBuffer global_vertex_buffer;
	VkDeviceMemory global_vertex_buffer_memory;

	VkBuffer global_projection_buffer;
	VkDeviceMemory global_projection_buffer_memory;
	VkBuffer global_lighting_info_buffer;
	VkDeviceMemory global_lighting_info_buffer_memory;

	// testing
	VkDescriptorImageInfo imageInfo = {};

	VkSampler _textureSampler;

	float lastFrame;

	Window _engineWindow;
	Device _engineDevice;
	Camera _camera;

	// private methods
	// init vulkan and main functions
	void init_vulkan();
	void init_scene();
	void main_loop();

	// initialization
	void create_instance();
	void init_textures();
	void init_materials();
	void init_meshes();
	void init_world();
	void init_all_textures();

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

	// buffers
	void create_global_projection_buffers();
	void create_command_pool();
	void create_command_buffers();
	void create_vertex_buffer();
	void create_index_buffer();

	// drawing
	void draw_frame();
	void create_sync_objects();
	void create_semaphores();

	// texture setup
	void create_texture_sampler();
	void add_texture(std::string textureName, const char* texturePath);

	void update_materials();
	void process_input();
};

static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
	auto engine = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window));
	engine->_frameBuffer_resized = true;
}
