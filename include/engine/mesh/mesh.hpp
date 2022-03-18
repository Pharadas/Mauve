#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include<engine/buffer_helper.hpp>

#include <iostream>

#include <vector>
#include <array>
#include <cstring>

struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 texCoord;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, normal);

        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

        return attributeDescriptions;
    }
};

class Mesh {
public:
    Mesh();
    Mesh(std::vector<Vertex> inputVertices);
    // Mesh(std::vector<Vertex> inputVertices, VkCommandPool commandPool, VkQueue graphicsQueue);
    // Mesh(std::vector<Vertex> inputVertices, std::vector<uint16_t> inputIndices, VkCommandPool commandPool, VkQueue graphicsQueue);

    void cleanup();
    void build(VkCommandPool commandPool, VkQueue graphicsQueue);
    void addTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);

    std::vector<Vertex>   vertices;
    std::vector<uint16_t> indices;

    bool isIndexed;
    VkBuffer vertexBuffer = VK_NULL_HANDLE;
    VkBuffer indexBuffer = VK_NULL_HANDLE;

private:
    void create_vertex_buffer(VkCommandPool commandPool, VkQueue graphicsQueue);
    void create_index_buffer(VkCommandPool commandPool, VkQueue graphicsQueue);

    VkDeviceSize vertexBufferSize;
    VkDeviceSize indicesBufferSize;
    VkDeviceMemory vertexBufferMemory = VK_NULL_HANDLE;
    VkDeviceMemory indicesBufferMemory = VK_NULL_HANDLE;
};
