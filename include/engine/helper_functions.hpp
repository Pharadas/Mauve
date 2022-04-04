#pragma once

#include <vulkan/vulkan.h>

#include <vector>
#include <string>
#include <fstream>

std::vector<char> readFile(const std::string& filename);

void create_image(uint32_t width, uint32_t height, uint32_t mipLevels, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

void generate_mip_maps(VkCommandPool commandPool, VkQueue graphicsQueue, VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);

VkImageView create_image_view(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);

VkFormat find_depth_format();

VkFormat find_supported_format(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
