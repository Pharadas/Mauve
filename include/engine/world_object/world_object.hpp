#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <array>
#include <cstring>
#include <vector>
#include <memory>

#include <engine/buffer_helper.hpp>
#include <engine/material/materials.hpp>

class WorldObject {
public:
    WorldObject(std::shared_ptr<Mesh> inputMesh, std::shared_ptr<Material> inputMaterial);
    void update_push_constants(glm::mat4 matrix);
    virtual void draw(VkCommandBuffer cmdBffr, int instance, MeshPushConstants pushConstants);

    Material* material;
    Mesh* mesh;

    glm::vec3 position = glm::vec3(0, 0, 0);
    glm::vec3 scale    = glm::vec3(1, 1, 1);
    glm::vec3 color;
    float xRotation = 0.f;
    float yRotation = 0.f;
    float zRotation = 0.f;
};

class TexturedWorldObject : public WorldObject {
public:
    TexturedWorldObject(std::shared_ptr<Mesh> inputMesh, std::shared_ptr<Material> inputMaterial, int texNum);
    virtual void draw(VkCommandBuffer cmdBffr, int instance, MeshPushConstants pushConstants);

	int texture;
};

class PointsWorldObject : public WorldObject {
public:
    PointsWorldObject(std::shared_ptr<Mesh> inputMesh, std::shared_ptr<Material> inputMaterial);
    virtual void draw(VkCommandBuffer cmdBffr, int instance, MeshPushConstants pushConstants);
};


// class TexturedLitWorldObject : public WorldObject {
// public:
//     TexturedLitWorldObject(Mesh* inputMesh, Textured_Lit_Material* inputMaterial, int texNum, glm::vec3 inputColor);
//     virtual void draw(VkCommandBuffer cmdBffr, int instance, MeshPushConstants pushConstants);

// private:
//     Textured_Lit_Material* material;
// 	int texture;
//     glm::vec3 color;
// };
