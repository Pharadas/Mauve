#include <engine/mesh/mesh.hpp>

// MESH IMPLEMENTATION ////////////////////////////////////////////////////////////////////////////
// Mesh::Mesh(std::vector<Vertex> inputVertices, VkCommandPool commandPool, VkQueue graphicsQueue) {
// 	vertices = inputVertices;

// 	create_vertex_buffer(commandPool, graphicsQueue);
// }

Mesh::Mesh() {}

Mesh::Mesh(std::vector<Vertex> inputVertices) {
	vertices = inputVertices;
}

// * Wrapper de create_vertex_buffer para que el usuario no tenga acceso a esta funcion
void Mesh::build(VkCommandPool commandPool, VkQueue graphicsQueue) {
	create_vertex_buffer(commandPool, graphicsQueue);
}

void Mesh::addTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) {
	glm::vec3 V = v2 - v1;
	glm::vec3 U = v3 - v1;

	glm::vec3 normal;

	normal.x = (U.y * V.z) - (U.z * V.y);
	normal.y = (U.z * V.x) - (U.x * V.z);
	normal.z = (U.x * V.y) - (U.y * V.x);

	vertices.push_back({v1, normal, {0, 1}});
	vertices.push_back({v2, normal, {1, 1}});
	vertices.push_back({v3, normal, {1, 0}});

	// std::cout << "{";
	// std::cout << "{" << v1.x << ", " << v1.y << ", " << v1.z << "},";
	// std::cout << "{" << normal.x << ", " << normal.y << ", " << normal.z << "},";
	// std::cout << "{1, 0}";
	// std::cout << "}\n";

	// std::cout << "{";
	// std::cout << "{" << v2.x << ", " << v2.y << ", " << v2.z << "},";
	// std::cout << "{" << normal.x << ", " << normal.y << ", " << normal.z << "},";
	// std::cout << "{1, 1}";
	// std::cout << "}\n";

	// std::cout << "{";
	// std::cout << "{" << v3.x << ", " << v3.y << ", " << v3.z << "},";
	// std::cout << "{" << normal.x << ", " << normal.y << ", " << normal.z << "},";
	// std::cout << "{0, 0}";
	// std::cout << "}\n";
}

void Mesh::create_index_buffer(VkCommandPool commandPool, VkQueue graphicsQueue) {
	indicesBufferSize = sizeof(indices[0]) * indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    create_buffer(indicesBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(_device, stagingBufferMemory, 0, indicesBufferSize, 0, &data);
		memcpy(data, indices.data(), (size_t) indicesBufferSize);
    vkUnmapMemory(_device, stagingBufferMemory);

    create_buffer(indicesBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indicesBufferMemory);

    copy_buffer(stagingBuffer, indexBuffer, indicesBufferSize, commandPool, graphicsQueue);

    vkDestroyBuffer(_device, stagingBuffer, nullptr);
    vkFreeMemory(_device, stagingBufferMemory, nullptr);
}

void Mesh::create_vertex_buffer(VkCommandPool commandPool, VkQueue graphicsQueue) {
	vertexBufferSize = sizeof(vertices[0]) * vertices.size();

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	create_buffer(vertexBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(_device, stagingBufferMemory, 0, vertexBufferSize, 0, &data);
		memcpy(data, vertices.data(), (size_t) vertexBufferSize);
	vkUnmapMemory(_device, stagingBufferMemory);

	create_buffer(vertexBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

	copy_buffer(stagingBuffer, vertexBuffer, vertexBufferSize, commandPool, graphicsQueue);

	vkDestroyBuffer(_device, stagingBuffer, nullptr);
	vkFreeMemory(_device, stagingBufferMemory, nullptr);
}

void Mesh::setVertices(std::vector<Vertex> inputVertices) {
	vertices = inputVertices;
}

void Mesh::cleanup() {
	vkDestroyBuffer(_device, vertexBuffer, nullptr);
	vkFreeMemory(_device, vertexBufferMemory, nullptr);
	vkDestroyBuffer(_device, indexBuffer, nullptr);
	vkFreeMemory(_device, indicesBufferMemory, nullptr);
}

