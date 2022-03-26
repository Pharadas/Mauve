#include <game/chunk.hpp>

Chunk::Chunk(glm::vec2 position, siv::PerlinNoise noise) {
   mesh = std::make_shared<Mesh>();

   std::vector<Vertex> atras = {
      // * atras ./
      {{0.5f,  0.5f, -0.5f}, {1, 1, 1},  {0.0f, 0.0f}},
      {{0.5f, -0.5f, -0.5f}, {1, 1, 1},  {0.0f, 1.0f}},
      {{-0.5f, -0.5f, -0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
      {{-0.5f, -0.5f, -0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
      {{-0.5f,  0.5f, -0.5f}, {1, 1, 1}, {1.0f, 0.0f}},
      {{0.5f,  0.5f, -0.5f}, {1, 1, 1},  {0.0f, 0.0f}},
   };

   std::vector<Vertex> frente = {
      // * frente ./
      {{-0.5f, -0.5f,  0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
      {{0.5f, -0.5f,  0.5f}, {1, 1, 1},  {0.0f, 1.0f}},
      {{0.5f,  0.5f,  0.5f}, {1, 1, 1},  {0.0f, 0.0f}},
      {{0.5f,  0.5f,  0.5f}, {1, 1, 1},  {0.0f, 0.0f}},
      {{-0.5f,  0.5f,  0.5f}, {1, 1, 1}, {1.0f, 0.0f}},
      {{-0.5f, -0.5f,  0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
   };

   std::vector<Vertex> izquierda = {
      // * izquierda ./
      {{-0.5f,  0.5f,  0.5f}, {1, 1, 1}, {0.0f, 0.0f}},
      {{-0.5f,  0.5f, -0.5f}, {1, 1, 1}, {1.0f, 0.0f}},
      {{-0.5f, -0.5f, -0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
      {{-0.5f, -0.5f, -0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
      {{-0.5f, -0.5f,  0.5f}, {1, 1, 1}, {0.0f, 1.0f}},
      {{-0.5f,  0.5f,  0.5f}, {1, 1, 1}, {0.0f, 0.0f}},
   };

   std::vector<Vertex> derecha = {
      // * Derecha ./
      {{0.5f, -0.5f, -0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
      {{0.5f,  0.5f, -0.5f}, {1, 1, 1}, {1.0f, 0.0f}},
      {{0.5f,  0.5f,  0.5f}, {1, 1, 1}, {0.0f, 0.0f}},
      {{0.5f,  0.5f,  0.5f}, {1, 1, 1}, {0.0f, 0.0f}},
      {{0.5f, -0.5f,  0.5f}, {1, 1, 1}, {0.0f, 1.0f}},
      {{0.5f, -0.5f, -0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
   };

   std::vector<Vertex> abajo = {
      // * Abajo ./
      {{-0.5f, -0.5f, -0.5f}, {1, 1, 1}, {0.0f, 1.0f}},
      {{0.5f, -0.5f, -0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
      {{0.5f, -0.5f,  0.5f}, {1, 1, 1}, {1.0f, 0.0f}},
      {{0.5f, -0.5f,  0.5f}, {1, 1, 1}, {1.0f, 0.0f}},
      {{-0.5f, -0.5f,  0.5f}, {1, 1, 1}, {0.0f, 0.0f}},
      {{-0.5f, -0.5f, -0.5f}, {1, 1, 1}, {0.0f, 1.0f}},
   };

   std::vector<Vertex> arriba = {
      // * Arriba ./
      {{0.5f,  0.5f, -0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
      {{-0.5f,  0.5f, -0.5f}, {1, 1, 1}, {0.0f, 1.0f}},
      {{0.5f,  0.5f,  0.5f}, {1, 1, 1}, {1.0f, 0.0f}},
      {{-0.5f,  0.5f, -0.5f}, {1, 1, 1}, {0.0f, 1.0f}},
      {{-0.5f,  0.5f,  0.5f}, {1, 1, 1}, {0.0f, 0.0f}},
      {{0.5f,  0.5f,  0.5f}, {1, 1, 1}, {1.0f, 0.0f}},
   };

         // for (int r = 0; r < world[x][y]; r++) {
         //    for (auto i : vertices) {
         //       glm::vec3 originalPosition = i.pos;
         //       glm::vec3 translatedPosition;

         //       translatedPosition.x = originalPosition.x + x;
         //       translatedPosition.y = originalPosition.y + r;
         //       translatedPosition.z = originalPosition.z + y;

         //       chunkVertices.push_back({{translatedPosition}, i.normal, i.texCoord});
         //    }
         // }

   for (int x = 0; x < chunkSize; x++) {
      for (int z = 0; z < chunkSize; z++) {
         const int height = int(noise.octave2D_01((x + (position.x * chunkSize)) * resolution, (z + (position.y * chunkSize)) * resolution, 8) * 10);
         for (int y = 0; y < chunkHeight; y++) {
            if (y > height) {
               chunkMap[x][y][z] = false;
            } else {
               chunkMap[x][y][z] = true;
            }
         }
		}
	}

   for (int x = 0; x < chunkSize; x++) {
      for (int z = 0; z < chunkSize; z++) {
         for (int y = 0; y < chunkHeight; y++) {
            if (chunkMap[x][y][z]) {
               if (!chunkMap[x + 1][y][z] && x + 1 < chunkSize) {
                  for (auto i : derecha) {
                     glm::vec3 originalPosition = i.pos;
                     glm::vec3 translatedPosition;

                     translatedPosition.x = originalPosition.x + x;
                     translatedPosition.y = originalPosition.y + y;
                     translatedPosition.z = originalPosition.z + z;

                     chunkVertices.push_back({{translatedPosition}, i.normal, i.texCoord});
                  }
               }

               if (!chunkMap[x - 1][y][z] && x - 1 > 0) {
                  for (auto i : izquierda) {
                     glm::vec3 originalPosition = i.pos;
                     glm::vec3 translatedPosition;

                     translatedPosition.x = originalPosition.x + x;
                     translatedPosition.y = originalPosition.y + y;
                     translatedPosition.z = originalPosition.z + z;

                     chunkVertices.push_back({{translatedPosition}, i.normal, i.texCoord});
                  }
               }

               if (!chunkMap[x][y + 1][z]) {
                  for (auto i : arriba) {
                     glm::vec3 originalPosition = i.pos;
                     glm::vec3 translatedPosition;

                     translatedPosition.x = originalPosition.x + x;
                     translatedPosition.y = originalPosition.y + y;
                     translatedPosition.z = originalPosition.z + z;

                     chunkVertices.push_back({{translatedPosition}, i.normal, i.texCoord});
                  }
               }

               if (!chunkMap[x][y - 1][z] && y - 1 > 0) {
                  for (auto i : abajo) {
                     glm::vec3 originalPosition = i.pos;
                     glm::vec3 translatedPosition;

                     translatedPosition.x = originalPosition.x + x;
                     translatedPosition.y = originalPosition.y + y;
                     translatedPosition.z = originalPosition.z + z;

                     chunkVertices.push_back({{translatedPosition}, i.normal, i.texCoord});
                  }
               }

               if (!chunkMap[x][y][z + 1] && z + 1 < chunkSize) {
                  for (auto i : frente) {
                     glm::vec3 originalPosition = i.pos;
                     glm::vec3 translatedPosition;

                     translatedPosition.x = originalPosition.x + x;
                     translatedPosition.y = originalPosition.y + y;
                     translatedPosition.z = originalPosition.z + z;

                     chunkVertices.push_back({{translatedPosition}, i.normal, i.texCoord});
                  }
               }

               if (!chunkMap[x][y][z - 1] && z - 1 > 0) {
                  for (auto i : atras) {
                     glm::vec3 originalPosition = i.pos;
                     glm::vec3 translatedPosition;

                     translatedPosition.x = originalPosition.x + x;
                     translatedPosition.y = originalPosition.y + y;
                     translatedPosition.z = originalPosition.z + z;

                     chunkVertices.push_back({{translatedPosition}, i.normal, i.texCoord});
                  }
               }
            }
         }
      }
   }

   mesh->setVertices(chunkVertices);
}
