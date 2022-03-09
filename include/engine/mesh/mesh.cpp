#include <engine/mesh/mesh.hpp>

// MESH IMPLEMENTATION ////////////////////////////////////////////////////////////////////////////
Mesh::Mesh(std::vector<Vertex> inputVertices, VkCommandPool commandPool, VkQueue graphicsQueue) {
	vertices = inputVertices;

	create_vertex_buffer(commandPool, graphicsQueue);
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

void Mesh::cleanup() {
	vkDestroyBuffer(_device, vertexBuffer, nullptr);
	vkFreeMemory(_device, vertexBufferMemory, nullptr);
	vkDestroyBuffer(_device, indexBuffer, nullptr);
	vkFreeMemory(_device, indicesBufferMemory, nullptr);
}

