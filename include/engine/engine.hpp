#pragma once

#include <engine/window/window.hpp>
#include <engine/device/device.hpp>

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdexcept>
#include <vector>

class Engine {
public:
	void run();

private:
	// private members
	Window _engineWindow;
	VkInstance _instance;
	const std::vector<const char*> _validationLayers = {"VK_LAYER_KHRONOS_validation"};
	bool _enableValidationLayers = true;
	VkDebugUtilsMessengerEXT _debugMessenger;

	Device _engineDevice;

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
};