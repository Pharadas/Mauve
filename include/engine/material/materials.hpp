#pragma once

#include <engine/descriptors/descriptor.hpp>
#include <engine/buffer_helper.hpp>
#include <engine/helper_functions.hpp>
#include <engine/mesh/mesh.hpp>
#include <engine/texture/texture.hpp>

#include <vulkan/vulkan.h>

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct MeshPushConstants {
	glm::vec4 data;
	glm::mat4 render_matrix;
};

class Material {
public:
    Material(VkRenderPass renderPass, VkExtent2D swapchainExtent);
    virtual void build_material_pipeline(char const* vertShaderPath, char const* fragShaderPath, VkRenderPass renderPass, VkExtent2D swapchainExtent);
    void record_draw_command(VkCommandBuffer cmdBffr);
    void rebuild_material();
    virtual void setup_descriptor_set(VkCommandBuffer cmdBffr);
    virtual void recreate(VkRenderPass renderPass, VkExtent2D swapchainExtent);
    virtual void cleanup();
    void resize_cleanup();
    VkShaderModule create_shader_module(const std::vector<char>& code);

    VkPipeline       pipeline;
    VkPipelineLayout pipelineLayout;

    VkDescriptorSet        descriptorSets;
    VkDescriptorSetLayout  descriptorSetLayout;
    DescriptorBuilder      builder;
    DescriptorAllocator    descriptorAllocator;
    DescriptorLayoutCache  descriptorLayoutCache;
    VkDescriptorBufferInfo descriptorBufferInfo;

private:

    VkDeviceMemory         bufferMemory;

    int maxObjects = 100;
    int currObject = 0;
};

class Textured_Material : public Material {
public:
    Textured_Material(Texture texture, VkSampler sampler, VkRenderPass renderPass, VkExtent2D swapchainExtent);
    virtual void build_material_pipeline(char const* vertShaderPath, char const* fragShaderPath, VkRenderPass renderPass, VkExtent2D swapchainExtent);
    virtual void setup_descriptor_set(VkCommandBuffer cmdBffr);
    virtual void recreate(VkRenderPass renderPass, VkExtent2D swapchainExtent);

private:
    // * Types y flags especificas de cada material, pero todas tienen transformaciones para 3d, asi que son estas por default
    std::vector<std::pair<VkDescriptorType, VkShaderStageFlags>> typesAndFlags = {
        {VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT} // Texture
    };
};
