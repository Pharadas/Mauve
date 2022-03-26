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

struct LightingInfo {
    glm::vec3 objectColor;
    glm::vec3 lightColor;
    glm::vec3 lightPos;
    glm::vec3 viewPos;
};

struct MeshPushConstants {
    int numOfTexture;
    int numOfObjectWithinMaterial;
	alignas(16) glm::mat4 modelMatrix;
};

struct VP {
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

class Material {
public:
    Material();
    virtual void build_material_pipeline(char const* vertShaderPath, char const* fragShaderPath, VkRenderPass renderPass, VkExtent2D swapchainExtent);
    void record_draw_command(VkCommandBuffer cmdBffr);
    void rebuild_material();
    virtual void setup_descriptor_set(VkCommandBuffer cmdBffr);
    virtual void recreate(VkRenderPass renderPass, VkExtent2D swapchainExtent);
    virtual void build(VkRenderPass renderPass, VkExtent2D swapchainExtent, VkBuffer globalProjectionBuffer);
    virtual void cleanup();
    void resize_cleanup();

    VkPipeline       pipeline;
    VkPipelineLayout pipelineLayout;

    VkDescriptorSet        descriptorSets;
    VkDescriptorSetLayout  descriptorSetLayouts;
    DescriptorBuilder      builder;
    DescriptorAllocator    descriptorAllocator;
    DescriptorLayoutCache  descriptorLayoutCache;
    VkDescriptorBufferInfo descriptorBufferInfo;

    int descriptorLayouts = 0;
    int maxObjects = 1000;

    int currObject = 0;

private:
    VkDeviceMemory         bufferMemory;
    std::vector<std::pair<VkDescriptorType, VkShaderStageFlags>> typesAndFlags = {
        {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT || VK_SHADER_STAGE_FRAGMENT_BIT}, // * Informacion de transformaciones
    };

    VkShaderModule create_shader_module(const std::vector<char>& code);
};

// * TEXTURED MATERIAL //////////////////////////////////////////////////////////////////////////////////////////////////////////
class Textured_Material : public Material {
public:
    Textured_Material();
    Textured_Material(std::vector<Texture> textures, VkSampler* sampler);
    virtual void setup_descriptor_set(VkCommandBuffer cmdBffr);
    virtual void build(VkRenderPass renderPass, VkExtent2D swapchainExtent, VkBuffer globalProjectionBuffer);
    virtual void recreate(VkRenderPass renderPass, VkExtent2D swapchainExtent);

private:
    std::vector<Texture> texturesVector;
    VkSampler* sampler;

    std::vector<std::pair<VkDescriptorType, VkShaderStageFlags>> typesAndFlags = {
        {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT || VK_SHADER_STAGE_FRAGMENT_BIT}, // * Informacion de transformaciones
        {VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT} // * Combined image sampler
    };
};

// // * TEXTURED LIT MATERIAL ///////////////////////////////////////////////////////////////////////////////////////////////////////

// class Textured_Lit_Material : public Material {
// public:
//     Textured_Lit_Material();
//     Textured_Lit_Material(std::vector<Texture> textures, VkSampler* sampler);
//     virtual void setup_descriptor_set(VkCommandBuffer cmdBffr);
//     virtual void recreate(VkRenderPass renderPass, VkExtent2D swapchainExtent);
//     void updateLightingInfo();

//     LightingInfo lightInfo;

// private:
//     VkBuffer       lightingUniformBuffer;
//     VkDeviceMemory lightingUniformBufferMemory;

//     // * Types y flags especificas de cada material, pero todas tienen transformaciones para 3d, asi que son estas por default
//     std::vector<std::pair<VkDescriptorType, VkShaderStageFlags>> typesAndFlags = {
//         {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, VK_SHADER_STAGE_VERTEX_BIT}, // * Informacion de transformaciones
//         {VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT}, // * Combined image sampler
//         {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_FRAGMENT_BIT}, // * Light info
//     };
// };
