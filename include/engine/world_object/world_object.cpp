#include <engine/world_object/world_object.hpp>
#include <iostream>

WorldObject::WorldObject(Mesh* inputMesh, Material* inputMaterial) {
    mesh = inputMesh;
    material = inputMaterial;
}

void WorldObject::draw(VkCommandBuffer cmdBffr, int instance, MeshPushConstants pushConstants) {
	vkCmdBindPipeline(cmdBffr, VK_PIPELINE_BIND_POINT_GRAPHICS, material->pipeline);
	material->setup_descriptor_set(cmdBffr);

	vkCmdPushConstants(cmdBffr, material->pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(MeshPushConstants), &pushConstants);
	VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(cmdBffr, 0, 1, &(mesh->vertexBuffer), &offset);

	// print << "grabando";

	vkCmdDraw(cmdBffr, mesh->vertices.size(), 1, 0, instance);
}

void WorldObject::cleanup() {
	// material->cleanup();
	// mesh->cleanup();
}
