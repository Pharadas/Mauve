// #include <game/chunk.hpp>

// Chunk::Chunk(glm::vec2 position, siv::PerlinNoise noise, VkCommandPool commandPool, VkQueue graphicsQueue, Material* inputMaterial) {
//    std::vector<Vertex> chunkVertices;

//    for (int y = 0; y < chunkSize; ++y) {
// 		for (int x = 0; x < chunkSize; ++x) {
// 			const double height = noise.octave2D_01((x), (y), 4, .1);

// 			world[x][y] = int(height * 10);

//          for (auto i : singleCube) {
//             glm::vec3 originalPosition = glm::vec3(i.pos.x * 0.5, i.pos.y * 0.5, i.pos.z * 0.5);
//             glm::vec3 translatedPosition;

//             translatedPosition.x = originalPosition.x + x;
//             translatedPosition.y = originalPosition.y + world[x][y];
//             translatedPosition.z = originalPosition.z + y;

//             chunkVertices.push_back({{translatedPosition}, i.normal, i.texCoord});
//          }
// 		}
// 	}

//    // chunkMesh.reset(new Mesh(chunkVertices, commandPool, graphicsQueue));

//    chunkRenderableObject.reset(new TexturedWorldObject(chunkMesh.get(), inputMaterial, 0));
// }
