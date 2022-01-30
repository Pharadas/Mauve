#include <engine/world_object/world_object.hpp>
#include <iostream>

WorldObject::WorldObject(Mesh* inputMesh, Material* inputMaterial) {
    mesh = inputMesh;
    material = inputMaterial;
}

void WorldObject::draw(VkCommandBuffer cmdBffr, int instance, MeshPushConstants pushConstants) {
	vkCmdBindPipeline(cmdBffr, VK_PIPELINE_BIND_POINT_GRAPHICS, material->pipeline);
	// material->setup_gpi(GPI, instance);
	material->setup_descriptor_set(cmdBffr);

	vkCmdPushConstants(cmdBffr, material->pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(MeshPushConstants), &pushConstants);
	VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(cmdBffr, 0, 1, &(mesh->vertexBuffer), &offset);

	vkCmdDraw(cmdBffr, mesh->vertices.size(), 1, 0, instance);
}

void WorldObject::cleanup() {
	material->cleanup();
	mesh->cleanup();
}

TexturedWorldObject::TexturedWorldObject(Mesh* inputMesh, Material* inputMaterial, int texNum) : WorldObject(inputMesh, inputMaterial) {
	mesh = inputMesh;
	material = inputMaterial;
	texture = texNum;
}

void TexturedWorldObject::draw(VkCommandBuffer cmdBffr, int instance, MeshPushConstants pushConstants) {
	// * La funcion draw() del objeto se encarga de actualizar el pushConstant con el numero de textura correcto
	pushConstants.numOfTexture = texture;

	vkCmdBindPipeline(cmdBffr, VK_PIPELINE_BIND_POINT_GRAPHICS, material->pipeline);
	material->setup_descriptor_set(cmdBffr);

	vkCmdPushConstants(cmdBffr, material->pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(MeshPushConstants), &pushConstants);
	VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(cmdBffr, 0, 1, &(mesh->vertexBuffer), &offset);

	vkCmdDraw(cmdBffr, mesh->vertices.size(), 1, 0, instance);
}

TexturedLitWorldObject::TexturedLitWorldObject(Mesh* inputMesh, Textured_Lit_Material* inputMaterial, int texNum, glm::vec3 inputColor) : WorldObject(inputMesh, inputMaterial) {
	mesh = inputMesh;
	material = inputMaterial;
	texture = texNum;
	color = inputColor;
}

void TexturedLitWorldObject::draw(VkCommandBuffer cmdBffr, int instance, MeshPushConstants pushConstants) {
	// * La funcion draw() del objeto se encarga de actualizar el pushConstant con el numero de textura correcto
	pushConstants.numOfTexture = texture;
	LightingInfo lightInfo = {};
		lightInfo.lightColor = glm::vec3(1.f, 1.f, 1.f);
		lightInfo.objectColor = color;

	vkCmdBindPipeline(cmdBffr, VK_PIPELINE_BIND_POINT_GRAPHICS, material->pipeline);
	// * Se hace un dynamic cast para poder acceder a la informacion especifica de la clase derivada
	dynamic_cast<Textured_Lit_Material*>(material)->lightInfo.lightColor = color;
	material->setup_descriptor_set(cmdBffr);

	vkCmdPushConstants(cmdBffr, material->pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(MeshPushConstants), &pushConstants);
	VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(cmdBffr, 0, 1, &(mesh->vertexBuffer), &offset);

	vkCmdDraw(cmdBffr, mesh->vertices.size(), 1, 0, instance);
}
