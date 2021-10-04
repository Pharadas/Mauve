#pragma once

#include <vulkan/vulkan.h>
#include <vector>

class Descriptors {
public:
    VkDescriptorSetLayout _descriptorSetLayout;
    std::vector<VkDescriptorSet> _descriptorSets;

    void create_descriptor_set_layout();
    void create_descriptor_pool(std::vector<VkImage> swapChainImages);
	void create_descriptor_sets(std::vector<VkImage> swapChainImages, std::vector<VkBuffer> uniformBuffers, VkImageView textureImageView, VkSampler textureSampler);

    void cleanup_descriptor_set_layouts();
    void destroy_pool();

private:
    VkDescriptorPool _descriptorPool;
};