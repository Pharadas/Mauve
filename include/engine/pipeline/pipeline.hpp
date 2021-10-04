#pragma once

#include <engine/helper_functions.hpp>
#include <vulkan/vulkan.h>

class Pipeline {
public:
    VkPipeline _graphicsPipeline;
    VkPipelineLayout _pipelineLayout;

    void create_graphics_pipeline(VkDevice device, VkExtent2D swapchainExtent, VkRenderPass renderPass, VkDescriptorSetLayout descriptorSetLayout);
    void cleanup(VkDevice device);

private: 

    VkShaderModule create_shader_module(const std::vector<char>& code, VkDevice device);
};