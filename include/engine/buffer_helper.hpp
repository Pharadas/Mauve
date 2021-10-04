#pragma once

#include <engine/device_data.hpp>

#include <vulkan/vulkan.h>
#include <stdexcept>

VkCommandBuffer begin_single_time_commands(VkCommandPool commandPool);

void end_single_time_commands(VkCommandPool commandPool, VkCommandBuffer commandBuffer, VkQueue graphicsQueue);

uint32_t find_memory_type(uint32_t typeFilter, VkMemoryPropertyFlags properties);

void create_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

void copy_buffer_to_image(VkCommandPool commandPool, VkQueue graphicsQueue, VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
