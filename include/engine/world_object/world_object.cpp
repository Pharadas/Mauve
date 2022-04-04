#include <engine/world_object/world_object.hpp>
#include <iostream>

WorldObject::WorldObject(std::shared_ptr<Mesh> inputMesh, std::shared_ptr<Material> inputMaterial) {
	mesh = inputMesh.get();
	material = inputMaterial.get();
}

void WorldObject::draw(VkCommandBuffer cmdBffr, int instance, MeshPushConstants pushConstants) {
	// * La funcion draw() del objeto se encarga de actualizar el pushConstant con el numero de textura correcto
	// * Preparar la push constant
	pushConstants.numOfObjectWithinMaterial = material->currObject;
	material->currObject++;

	glm::mat4 model{1.f};
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(1, 1, 1));
		model = glm::scale(model, scale);
		model = glm::translate(model, position);
		pushConstants.modelMatrix = model;

	vkCmdPushConstants(cmdBffr, material->pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(MeshPushConstants), &pushConstants);
	VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(cmdBffr, 0, 1, &(mesh->vertexBuffer), &offset);

	if (mesh->isIndexed) { 
		vkCmdBindIndexBuffer(cmdBffr, mesh->indexBuffer, offset, VK_INDEX_TYPE_UINT16);
		vkCmdDrawIndexed(cmdBffr, mesh->indices.size(), 1, 0, 0, instance);
	} else {
		vkCmdDraw(cmdBffr, mesh->vertices.size(), 1, 0, instance);
	}
}

TexturedWorldObject::TexturedWorldObject(std::shared_ptr<Mesh> inputMesh, std::shared_ptr<Material> inputMaterial, int texNum) : WorldObject(inputMesh, inputMaterial) {
	mesh = inputMesh.get();
	material = inputMaterial.get();
	texture = texNum;
}

void TexturedWorldObject::draw(VkCommandBuffer cmdBffr, int instance, MeshPushConstants pushConstants) {
	// * La funcion draw() del objeto se encarga de actualizar el pushConstant con el numero de textura correcto
	// * Preparar la push constant
	pushConstants.numOfTexture = texture;
	pushConstants.numOfObjectWithinMaterial = material->currObject;
	material->currObject++;

	glm::mat4 model{1.f};
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(1, 1, 1));
		model = glm::scale(model, scale);
		model = glm::translate(model, position);
		pushConstants.modelMatrix = model;

	material->setup_descriptor_set(cmdBffr);

	vkCmdPushConstants(cmdBffr, material->pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(MeshPushConstants), &pushConstants);
	VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(cmdBffr, 0, 1, &(mesh->vertexBuffer), &offset);
	if (mesh->isIndexed) { 
		vkCmdBindIndexBuffer(cmdBffr, mesh->indexBuffer, offset, VK_INDEX_TYPE_UINT16);
		vkCmdDrawIndexed(cmdBffr, mesh->indices.size(), 1, 0, 0, instance);
	} else {
		vkCmdDraw(cmdBffr, mesh->vertices.size(), 1, 0, instance);
	}
}

PointsWorldObject::PointsWorldObject(std::shared_ptr<Mesh> inputMesh, std::shared_ptr<Material> inputMaterial) : WorldObject(inputMesh, inputMaterial) {
	mesh = inputMesh.get();
	material = inputMaterial.get();
}

void PointsWorldObject::draw(VkCommandBuffer cmdBffr, int instance, MeshPushConstants pushConstants) {
	// * La funcion draw() del objeto se encarga de actualizar el pushConstant con el numero de textura correcto
	// * Preparar la push constant
	pushConstants.numOfObjectWithinMaterial = material->currObject;
	material->currObject++;

	glm::mat4 model{1.f};
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(1, 1, 1));
		model = glm::scale(model, scale);
		model = glm::translate(model, position);
		pushConstants.modelMatrix = model;

	material->setup_descriptor_set(cmdBffr);

	vkCmdPushConstants(cmdBffr, material->pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(MeshPushConstants), &pushConstants);
	VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(cmdBffr, 0, 1, &(mesh->vertexBuffer), &offset);
	if (mesh->isIndexed) { 
		vkCmdBindIndexBuffer(cmdBffr, mesh->indexBuffer, offset, VK_INDEX_TYPE_UINT16);
		vkCmdDrawIndexed(cmdBffr, mesh->indices.size(), 1, 0, 0, instance);
	} else {
		vkCmdDraw(cmdBffr, mesh->vertices.size(), 1, 0, instance);
	}
}


// TexturedLitWorldObject::TexturedLitWorldObject(Mesh* inputMesh, Textured_Lit_Material* inputMaterial, int texNum, glm::vec3 inputColor) : WorldObject(inputMesh, inputMaterial) {
// 	mesh = inputMesh;
// 	material = inputMaterial;
// 	texture = texNum;
// 	color = inputColor;
// }

// void TexturedLitWorldObject::draw(VkCommandBuffer cmdBffr, int instance, MeshPushConstants pushConstants) {
// 	// * La funcion draw() del objeto se encarga de actualizar el pushConstant con el numero de textura correcto
// 	pushConstants.numOfTexture = texture;
// 	pushConstants.numOfObjectWithinMaterial = material->currObject;
// 	material->currObject++;

// 	vkCmdBindPipeline(cmdBffr, VK_PIPELINE_BIND_POINT_GRAPHICS, material->pipeline);
// 	material->setup_descriptor_set(cmdBffr);

// 	vkCmdPushConstants(cmdBffr, material->pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(MeshPushConstants), &pushConstants);
// 	VkDeviceSize offset = 0;
// 	vkCmdBindVertexBuffers(cmdBffr, 0, 1, &(mesh->vertexBuffer), &offset);

// 	vkCmdDraw(cmdBffr, mesh->vertices.size(), 1, 0, instance);
// }

