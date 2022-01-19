#pragma once

#include <glm/glm.hpp>
#include <array>
#include <cstring>
#include <vector>

#include <engine/buffer_helper.hpp>
#include <engine/material/materials.hpp>

class WorldObject {
public:
    WorldObject(Mesh* inputMesh, Material* inputMaterial);
    void update_push_constants(glm::mat4 matrix);
    virtual void draw(VkCommandBuffer cmdBffr, int instance, MeshPushConstants pushConstants);
    void cleanup();

    Material* material;
    Mesh* mesh;

    glm::vec3 position = glm::vec3(0, 0, 0);
    glm::vec3 scale = glm::vec3(1, 1, 1);
    float rotation = 0.f;
    int numTex;

private:
    VkBuffer       globalBuffer;
    VkDeviceMemory globalBufferMemory;
};

// class TexturedWorldObject : WorldObject {
// public:
//     TexturedWorldObject(Mesh* inputMesh, Textured_Material* inputMaterial, std::string inputTexture);
//     // virtual void draw(VkCommandBuffer cmdBffr, int instance, MeshPushConstants pushConstants);

// 	std::string texture;
// };
