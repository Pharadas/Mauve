#include <game/chunk.hpp>

// * Solo para lo de la clase
#include <random>

float getHeight(glm::vec2 position, siv::PerlinNoise noise, int x, int z, int chunkSize, float resolution) { 
   return noise.octave2D_01((x + (position.x * chunkSize)) * resolution, (z + (position.y * chunkSize)) * resolution, 8) * 15;
}

GameChunk::GameChunk(glm::vec2 position, siv::PerlinNoise noise, bool puntos) {
   std::random_device rd; // obtain a random number from hardware
   std::mt19937 gen(rd()); // seed the generator
   std::uniform_real_distribution<> xzDistr(0, chunkSize); // define the range
   std::uniform_real_distribution<> yDistr(0, 15); // define the range

   chunkMesh = std::make_shared<Mesh>();

   if (!puntos) {
      for (int x = 0; x < chunkSize; x++) {
         for (int z = 0; z < chunkSize; z++) {
            // const float height = noise.octave2D_01((x + (position.x * chunkSize)) * resolution, (z + (position.y * chunkSize)) * resolution, 8) * 10;
            float height = 0;

            // mesh.get()->vertices.push_back({{x,     5 * sin(x), z},             {1, 1, 1}, {0, 0}});
            // mesh.get()->vertices.push_back({{x,     5 * sin(x), z + 1},     {1, 1, 1}, {0, 1}});
            // mesh.get()->vertices.push_back({{x + 1, 5 * sin(x + 1), z + 1}, {1, 1, 1}, {1, 1}});

            // mesh.get()->vertices.push_back({{x + 1, 5 * sin(x + 1), z + 1}, {1, 1, 1}, {1, 1}});
            // mesh.get()->vertices.push_back({{x + 1, 5 * sin(x + 1), z},         {1, 1, 1}, {1, 0}});
            // mesh.get()->vertices.push_back({{x,     5 * sin(x), z},             {1, 1, 1}, {0, 0}});

            chunkMesh.get()->vertices.push_back({{x,     getHeight(position, noise, x, z, chunkSize, resolution), z},             {0., 0., 1.}, {0, 0}});
            chunkMesh.get()->vertices.push_back({{x,     getHeight(position, noise, x, z + 1, chunkSize, resolution), z + 1},     {0., 0., 1.}, {0, 1}});
            chunkMesh.get()->vertices.push_back({{x + 1, getHeight(position, noise, x + 1, z + 1, chunkSize, resolution), z + 1}, {0., 0., 1.}, {1, 1}});

            chunkMesh.get()->vertices.push_back({{x + 1, getHeight(position, noise, x + 1, z + 1, chunkSize, resolution), z + 1}, {0., 0., 1.}, {1, 1}});
            chunkMesh.get()->vertices.push_back({{x + 1, getHeight(position, noise, x + 1, z, chunkSize, resolution), z},         {0., 0., 1.}, {1, 0}});
            chunkMesh.get()->vertices.push_back({{x,     getHeight(position, noise, x, z, chunkSize, resolution), z},             {0., 0., 1.}, {0, 0}});
         }
      }
   } else {
      int puntosDentro = 0;

      for (int i = 0; i < cantidadDePuntos; i++) {
         glm::vec3 currPosition(xzDistr(gen), yDistr(gen), xzDistr(gen));

         if (getHeight(position, noise, currPosition.x, currPosition.z, chunkSize, resolution) > currPosition.y) {
            chunkMesh.get()->vertices.push_back({{currPosition},{0., 1, 0.}, {0, 0}});
            puntosDentro++;
         } else {
            chunkMesh.get()->vertices.push_back({{currPosition},{1., 0., 0.}, {0, 0}});
         }
      }

      // std::cout << (16.*16.)*(float(puntosDentro) / float(cantidadDePuntos)) << '\n';
   }

   // std::vector<Vertex> atras = {
   //    // * atras ./
   //    {{0.5f,  0.5f, -0.5f}, {1, 1, 1},  {0.0f, 0.0f}},
   //    {{0.5f, -0.5f, -0.5f}, {1, 1, 1},  {0.0f, 1.0f}},
   //    {{-0.5f, -0.5f, -0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
   //    {{-0.5f, -0.5f, -0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
   //    {{-0.5f,  0.5f, -0.5f}, {1, 1, 1}, {1.0f, 0.0f}},
   //    {{0.5f,  0.5f, -0.5f}, {1, 1, 1},  {0.0f, 0.0f}},
   // };

   // std::vector<Vertex> frente = {
   //    // * frente ./
   //    {{-0.5f, -0.5f,  0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
   //    {{0.5f, -0.5f,  0.5f}, {1, 1, 1},  {0.0f, 1.0f}},
   //    {{0.5f,  0.5f,  0.5f}, {1, 1, 1},  {0.0f, 0.0f}},
   //    {{0.5f,  0.5f,  0.5f}, {1, 1, 1},  {0.0f, 0.0f}},
   //    {{-0.5f,  0.5f,  0.5f}, {1, 1, 1}, {1.0f, 0.0f}},
   //    {{-0.5f, -0.5f,  0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
   // };

   // std::vector<Vertex> izquierda = {
   //    // * izquierda ./
   //    {{-0.5f,  0.5f,  0.5f}, {1, 1, 1}, {0.0f, 0.0f}},
   //    {{-0.5f,  0.5f, -0.5f}, {1, 1, 1}, {1.0f, 0.0f}},
   //    {{-0.5f, -0.5f, -0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
   //    {{-0.5f, -0.5f, -0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
   //    {{-0.5f, -0.5f,  0.5f}, {1, 1, 1}, {0.0f, 1.0f}},
   //    {{-0.5f,  0.5f,  0.5f}, {1, 1, 1}, {0.0f, 0.0f}},
   // };

   // std::vector<Vertex> derecha = {
   //    // * Derecha ./
   //    {{0.5f, -0.5f, -0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
   //    {{0.5f,  0.5f, -0.5f}, {1, 1, 1}, {1.0f, 0.0f}},
   //    {{0.5f,  0.5f,  0.5f}, {1, 1, 1}, {0.0f, 0.0f}},
   //    {{0.5f,  0.5f,  0.5f}, {1, 1, 1}, {0.0f, 0.0f}},
   //    {{0.5f, -0.5f,  0.5f}, {1, 1, 1}, {0.0f, 1.0f}},
   //    {{0.5f, -0.5f, -0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
   // };

   // std::vector<Vertex> abajo = {
   //    // * Abajo ./
   //    {{-0.5f, -0.5f, -0.5f}, {1, 1, 1}, {0.0f, 1.0f}},
   //    {{0.5f, -0.5f, -0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
   //    {{0.5f, -0.5f,  0.5f}, {1, 1, 1}, {1.0f, 0.0f}},
   //    {{0.5f, -0.5f,  0.5f}, {1, 1, 1}, {1.0f, 0.0f}},
   //    {{-0.5f, -0.5f,  0.5f}, {1, 1, 1}, {0.0f, 0.0f}},
   //    {{-0.5f, -0.5f, -0.5f}, {1, 1, 1}, {0.0f, 1.0f}},
   // };

   // std::vector<Vertex> arriba = {
   //    // * Arriba ./
   //    {{0.5f,  0.5f, -0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
   //    {{-0.5f,  0.5f, -0.5f}, {1, 1, 1}, {0.0f, 1.0f}},
   //    {{0.5f,  0.5f,  0.5f}, {1, 1, 1}, {1.0f, 0.0f}},
   //    {{-0.5f,  0.5f, -0.5f}, {1, 1, 1}, {0.0f, 1.0f}},
   //    {{-0.5f,  0.5f,  0.5f}, {1, 1, 1}, {0.0f, 0.0f}},
   //    {{0.5f,  0.5f,  0.5f}, {1, 1, 1}, {1.0f, 0.0f}},
   // };

   //       // for (int r = 0; r < world[x][y]; r++) {
   //       //    for (auto i : vertices) {
   //       //       glm::vec3 originalPosition = i.pos;
   //       //       glm::vec3 translatedPosition;

   //       //       translatedPosition.x = originalPosition.x + x;
   //       //       translatedPosition.y = originalPosition.y + r;
   //       //       translatedPosition.z = originalPosition.z + y;

   //       //       chunkVertices.push_back({{translatedPosition}, i.normal, i.texCoord});
   //       //    }
   //       // }

   // for (int x = 0; x < chunkSize; x++) {
   //    for (int z = 0; z < chunkSize; z++) {
   //       const int height = int(noise.octave2D_01((x + (position.x * chunkSize)) * resolution, (z + (position.y * chunkSize)) * resolution, 8) * 10);
   //       for (int y = 0; y < chunkHeight; y++) {
   //          if (y > height) {
   //             chunkMap[x][y][z] = false;
   //          } else {
   //             chunkMap[x][y][z] = true;
   //          }
   //       }
	// 	}
	// }

   // for (int x = 0; x < chunkSize; x++) {
   //    for (int z = 0; z < chunkSize; z++) {
   //       for (int y = 0; y < chunkHeight; y++) {
   //          if (chunkMap[x][y][z]) {
   //             if (!chunkMap[x + 1][y][z] && x + 1 < chunkSize) {
   //                for (auto i : derecha) {
   //                   glm::vec3 originalPosition = i.pos;
   //                   glm::vec3 translatedPosition;

   //                   translatedPosition.x = originalPosition.x + x;
   //                   translatedPosition.y = originalPosition.y + y;
   //                   translatedPosition.z = originalPosition.z + z;

   //                   chunkVertices.push_back({{translatedPosition}, i.normal, i.texCoord});
   //                }
   //             }

   //             if (!chunkMap[x - 1][y][z] && x - 1 > 0) {
   //                for (auto i : izquierda) {
   //                   glm::vec3 originalPosition = i.pos;
   //                   glm::vec3 translatedPosition;

   //                   translatedPosition.x = originalPosition.x + x;
   //                   translatedPosition.y = originalPosition.y + y;
   //                   translatedPosition.z = originalPosition.z + z;

   //                   chunkVertices.push_back({{translatedPosition}, i.normal, i.texCoord});
   //                }
   //             }

   //             if (!chunkMap[x][y + 1][z]) {
   //                for (auto i : arriba) {
   //                   glm::vec3 originalPosition = i.pos;
   //                   glm::vec3 translatedPosition;

   //                   translatedPosition.x = originalPosition.x + x;
   //                   translatedPosition.y = originalPosition.y + y;
   //                   translatedPosition.z = originalPosition.z + z;

   //                   chunkVertices.push_back({{translatedPosition}, i.normal, i.texCoord});
   //                }
   //             }

   //             if (!chunkMap[x][y - 1][z] && y - 1 > 0) {
   //                for (auto i : abajo) {
   //                   glm::vec3 originalPosition = i.pos;
   //                   glm::vec3 translatedPosition;

   //                   translatedPosition.x = originalPosition.x + x;
   //                   translatedPosition.y = originalPosition.y + y;
   //                   translatedPosition.z = originalPosition.z + z;

   //                   chunkVertices.push_back({{translatedPosition}, i.normal, i.texCoord});
   //                }
   //             }

   //             if (!chunkMap[x][y][z + 1] && z + 1 < chunkSize) {
   //                for (auto i : frente) {
   //                   glm::vec3 originalPosition = i.pos;
   //                   glm::vec3 translatedPosition;

   //                   translatedPosition.x = originalPosition.x + x;
   //                   translatedPosition.y = originalPosition.y + y;
   //                   translatedPosition.z = originalPosition.z + z;

   //                   chunkVertices.push_back({{translatedPosition}, i.normal, i.texCoord});
   //                }
   //             }

   //             if (!chunkMap[x][y][z - 1] && z - 1 > 0) {
   //                for (auto i : atras) {
   //                   glm::vec3 originalPosition = i.pos;
   //                   glm::vec3 translatedPosition;

   //                   translatedPosition.x = originalPosition.x + x;
   //                   translatedPosition.y = originalPosition.y + y;
   //                   translatedPosition.z = originalPosition.z + z;

   //                   chunkVertices.push_back({{translatedPosition}, i.normal, i.texCoord});
   //                }
   //             }
   //          }
   //       }
   //    }
   // }

   // mesh->setVertices(chunkVertices);
}