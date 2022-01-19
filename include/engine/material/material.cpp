#include <engine/material/materials.hpp>
#include <iostream>

Material::Material(VkRenderPass renderPass, VkExtent2D swapchainExtent) {
    build_material_pipeline("shaders/basic.vert.spv", "shaders/basic.frag.spv", renderPass, swapchainExtent);
}

void Material::setup_descriptor_set(VkCommandBuffer cmdBffr) {}

// void Material::build(VkRenderPass renderPass, VkExtent2D swapchainExtent) {
    // create buffer to hold all objects info that this material could hold (default is 1000) objects)
    // create_buffer(sizeof(GlobalBufferObject) * maxObjects,  VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, descriptorBufferInfo.buffer, bufferMemory);
    // create_buffer(sizeof(GlobalBufferObject) * maxObjects, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, descriptorBufferInfo.buffer, bufferMemory);
    // descriptorBufferInfo.offset = 0;
    // descriptorBufferInfo.range = sizeof(GlobalBufferObject) * maxObjects;

    // * Build the descriptor sets
    // builder = DescriptorBuilder::begin(&descriptorLayoutCache, &descriptorAllocator);
    // builder.bind_buffer(0, &descriptorBufferInfo, typesAndFlags[0].first, typesAndFlags[0].second);
    // builder.build(descriptorSets, descriptorSetLayout);

    // build material pipeline
    // build_material_pipeline("shaders/basic.vert.spv", "shaders/basic.frag.spv", renderPass, swapchainExtent);
    // vkMapMemory(_device, bufferMemory, 0, sizeof(GlobalBufferObject) * maxObjects, 0, &globalObjectsData);
// }

// void Material::add_object_to_draw_buffer(GlobalBufferObject ubo) {
//     GlobalBufferObject* storageBuffer = (GlobalBufferObject*) globalObjectsData;
//     storageBuffer[1] = ubo;
//     currObject++;
//     globalObjectsData = storageBuffer;
// }

void Material::build_material_pipeline(char const* vertShaderPath, char const* fragShaderPath, VkRenderPass renderPass, VkExtent2D swapchainExtent) {
    auto vertShaderCode = readFile(vertShaderPath);
    auto fragShaderCode = readFile(fragShaderPath);

    VkShaderModule vertShaderModule = create_shader_module(vertShaderCode);
    VkShaderModule fragShaderModule = create_shader_module(fragShaderCode);

    VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
        vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vertShaderStageInfo.module = vertShaderModule;
        vertShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
        fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        fragShaderStageInfo.module = fragShaderModule;
        fragShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
        vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

        auto bindingDescription = Vertex::getBindingDescription();
        auto attributeDescriptions = Vertex::getAttributeDescriptions();

        vertexInputInfo.vertexBindingDescriptionCount = 1;
        vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
        vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
        vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
        inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        inputAssembly.primitiveRestartEnable = VK_FALSE;

    VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float) swapchainExtent.width;
        viewport.height = (float) swapchainExtent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

    VkRect2D scissor{};
        scissor.offset = {0, 0};
        scissor.extent = swapchainExtent;

    VkPipelineViewportStateCreateInfo viewportState{};
        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState.viewportCount = 1;
        viewportState.pViewports = &viewport;
        viewportState.scissorCount = 1;
        viewportState.pScissors = &scissor;

    VkPipelineRasterizationStateCreateInfo rasterizer{};
        rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizer.depthClampEnable = VK_FALSE;
        rasterizer.rasterizerDiscardEnable = VK_FALSE;
        rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
        rasterizer.lineWidth = 1.0f;
        // rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
        rasterizer.cullMode = VK_CULL_MODE_NONE;
        rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        rasterizer.depthBiasEnable = VK_FALSE;

    VkPipelineMultisampleStateCreateInfo multisampling{};
        multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampling.sampleShadingEnable = VK_FALSE;
        multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    VkPipelineDepthStencilStateCreateInfo depthStencil{};
        depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        depthStencil.depthTestEnable = VK_TRUE;
        depthStencil.depthWriteEnable = VK_TRUE;
        depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
        depthStencil.depthBoundsTestEnable = VK_FALSE;
        depthStencil.stencilTestEnable = VK_FALSE;

    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
        colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        colorBlendAttachment.blendEnable = VK_FALSE;

    VkPipelineColorBlendStateCreateInfo colorBlending{};
        colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        colorBlending.logicOpEnable = VK_FALSE;
        colorBlending.logicOp = VK_LOGIC_OP_COPY;
        colorBlending.attachmentCount = 1;
        colorBlending.pAttachments = &colorBlendAttachment;
        colorBlending.blendConstants[0] = 0.0f;
        colorBlending.blendConstants[1] = 0.0f;
        colorBlending.blendConstants[2] = 0.0f;
        colorBlending.blendConstants[3] = 0.0f;

    // PUSH CONSTANTS
	VkPushConstantRange push_constant;
        push_constant.offset = 0;
        push_constant.size = sizeof(MeshPushConstants);
        push_constant.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = descriptorLayouts;
        pipelineLayoutInfo.pSetLayouts = &descriptorSetLayouts;
        pipelineLayoutInfo.pushConstantRangeCount = 1;
        pipelineLayoutInfo.pPushConstantRanges = &push_constant;

    if (vkCreatePipelineLayout(_device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create pipeline layout!");
    }

    // * Conectar todo
    VkGraphicsPipelineCreateInfo pipelineInfo{};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineInfo.stageCount = 2;
        pipelineInfo.pStages = shaderStages;
        pipelineInfo.pVertexInputState = &vertexInputInfo;
        pipelineInfo.pInputAssemblyState = &inputAssembly;
        pipelineInfo.pViewportState = &viewportState;
        pipelineInfo.pRasterizationState = &rasterizer;
        pipelineInfo.pMultisampleState = &multisampling;
        pipelineInfo.pDepthStencilState = &depthStencil;
        pipelineInfo.pColorBlendState = &colorBlending;
        pipelineInfo.layout = pipelineLayout;
        pipelineInfo.renderPass = renderPass;
        pipelineInfo.subpass = 0;
        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

    if (vkCreateGraphicsPipelines(_device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &pipeline) != VK_SUCCESS) {
        throw std::runtime_error("failed to create graphics pipeline!");
    }

    vkDestroyShaderModule(_device, fragShaderModule, nullptr);
    vkDestroyShaderModule(_device, vertShaderModule, nullptr);
}

void Material::resize_cleanup() {
    vkDestroyPipelineLayout(_device, pipelineLayout, nullptr);
    vkDestroyPipeline(_device, pipeline, nullptr);
}

void Material::cleanup() {
    vkDestroyPipelineLayout(_device, pipelineLayout, nullptr);
    vkDestroyPipeline(_device, pipeline, nullptr);

    // vkDestroyDescriptorSetLayout(_device, descriptorSetLayout, nullptr);
    descriptorAllocator.cleanup();
    descriptorLayoutCache.cleanup();
}

void Material::recreate(VkRenderPass renderPass, VkExtent2D swapchainExtent) {
    resize_cleanup();
    build_material_pipeline("shaders/basic.vert.spv", "shaders/basic.frag.spv", renderPass, swapchainExtent);
}

VkShaderModule Material::create_shader_module(const std::vector<char>& code) {
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    VkShaderModule shaderModule;
    if (vkCreateShaderModule(_device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
        throw std::runtime_error("failed to create shader module!");
    }

    return shaderModule;
}

Textured_Material::Textured_Material(std::vector<VkImageView> textures, VkSampler* sampler, VkRenderPass renderPass, VkExtent2D swapchainExtent) : Material(renderPass, swapchainExtent) {
    std::vector<VkDescriptorImageInfo> imagesInfo(textures.size());
    for (size_t i = 0; i < textures.size(); i++) {
        imagesInfo[i].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        imagesInfo[i].imageView = textures[i];
        imagesInfo[i].sampler = VK_NULL_HANDLE;
    }

    descriptorLayouts = 1;
    // * Build the descriptor sets
    builder = DescriptorBuilder::begin(&descriptorLayoutCache, &descriptorAllocator);
        builder.bind_sampler(0, sampler, descriptorSets, typesAndFlags[0].first, typesAndFlags[0].second);
        builder.bind_image(1, imagesInfo, descriptorSets, typesAndFlags[1].first, typesAndFlags[1].second);
    builder.build(descriptorSets, descriptorSetLayouts);

    // build material pipeline
    build_material_pipeline("shaders/basic_textured.vert.spv", "shaders/basic_textured.frag.spv", renderPass, swapchainExtent);
}

void Textured_Material::setup_descriptor_set(VkCommandBuffer cmdBffr) {
	// vkCmdBindDescriptorSets(cmdBffr, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets, 0, 0);
	vkCmdBindDescriptorSets(cmdBffr, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets, 0, 0);
}

void Textured_Material::recreate(VkRenderPass renderPass, VkExtent2D swapchainExtent) {
    resize_cleanup();
    build_material_pipeline("shaders/basic_textured.vert.spv", "shaders/basic_textured.frag.spv", renderPass, swapchainExtent);
}

// Textured_Lit_Material::Textured_Lit_Material(Texture texture, VkSampler sampler, VkRenderPass renderPass, VkExtent2D swapchainExtent) : Material(renderPass, swapchainExtent) {

// }
