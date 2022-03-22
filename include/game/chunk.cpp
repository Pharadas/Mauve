#include <game/chunk.hpp>

Chunk::Chunk(glm::vec2 position, siv::PerlinNoise noise) {
   mesh = std::make_shared<Mesh>();

   float vertices[] = {
      // * atras ./
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

      // * frente ./
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

      // * izquierda ./
      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      // * Derecha ./
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

      // * Abajo ./
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

      // * Arriba
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
   };

   for (int y = 0; y < chunkSize; y++) {
		for (int x = 0; x < chunkSize; x++) {
			const double height = noise.octave2D_01((x + (position.x * chunkSize)) * (1. / chunkSize), (y + (position.y * chunkSize)) * (1. / chunkSize), 8);

			world[x][y] = int(height * 10);

         for (int r = 0; r < world[x][y]; r++) {
            for (int i = 0; i < 180; i += 5) {
               glm::vec3 originalPosition = glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]);
               glm::vec3 translatedPosition;

               translatedPosition.x = originalPosition.x + x;
               translatedPosition.y = originalPosition.y + r;
               translatedPosition.z = originalPosition.z + y;

               chunkVertices.push_back({{translatedPosition}, {0, 0, 0}, {vertices[i + 3], vertices[i + 4]}});
            }
         }
         // for (auto i : singleCube) {
         //    glm::vec3 originalPosition = glm::vec3(i.pos.x * 0.5, i.pos.y * 0.5, i.pos.z * 0.5);
         //    glm::vec3 translatedPosition;

         //    translatedPosition.x = originalPosition.x + x;
         //    translatedPosition.y = originalPosition.y + world[x][y];
         //    translatedPosition.z = originalPosition.z + y;

         //    chunkVertices.push_back({{translatedPosition}, i.normal, i.texCoord});
         // }
		}
	}

   mesh->setVertices(chunkVertices);
}
