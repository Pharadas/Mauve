#pragma once

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

class Device {
public:
	VkDevice _device;
	VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;

	VkQueue _graphicsQueue;
	VkQueue _presentQueue;

	VkSurfaceKHR* _surface;

	void pick_physical_device(VkInstance instance, VkSurfaceKHR* surface);
	void create_logical_device(bool enableValidationLayers, std::vector<const char*> validationLayers);

private:
	bool is_device_suitable(VkPhysicalDevice device);
	QueueFamilyIndices find_queue_families(VkPhysicalDevice device);
};
