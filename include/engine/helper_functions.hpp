#pragma once

#include <vulkan/vulkan.h>

#include <vector>
#include <string>
#include <fstream>

std::vector<char> readFile(const std::string& filename);

void create_image(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

VkImageView create_image_view(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

VkFormat find_depth_format();

VkFormat find_supported_format(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
