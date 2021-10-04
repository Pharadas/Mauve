#pragma once

#include <engine/device_data.hpp>

#include <vulkan/vulkan.h>
#include <experimental/optional>
#include <optional>
#include <vector>

struct QueueFamilyIndices {
	std::experimental::optional<uint32_t> graphicsFamily;
	std::experimental::optional<uint32_t> presentFamily;

	bool isComplete() {
		// necesita el && porque solo asi detecta que quiero el overload que regresa un bool
		return graphicsFamily && presentFamily;
	}
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class Device {
public:
	// VkDevice _device;
	// VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;

	VkQueue _graphicsQueue;
	VkQueue _presentQueue;

	VkSurfaceKHR _surface = VK_NULL_HANDLE;

	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	void pick_physical_device(VkInstance instance, VkSurfaceKHR surface);
	void create_logical_device(bool enableValidationLayers, std::vector<const char*> validationLayers);
	SwapChainSupportDetails query_swap_chain_support(VkPhysicalDevice device);
	VkSurfaceFormatKHR choose_swap_surface_format(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR choose_swap_present_mode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	QueueFamilyIndices find_queue_families(VkPhysicalDevice device);

private:
	bool is_device_suitable(VkPhysicalDevice device);
	bool check_device_extension_support(VkPhysicalDevice device);
};
