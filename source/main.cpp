// #define REBUILD_PROJECT

#ifndef REBUILD_PROJECT
    #include <vulkan/vulkan.h>
    #include <engine/engine.hpp>
    #include <game/chunk.hpp>

    #include <memory>
    #include <iostream>
    #include <string>
    #include <stdexcept>
    #include <cstdlib>

    #include <vector>
    #include <string>

	// Noise
	const siv::PerlinNoise::seed_type seed = int(rand() % 100);
	const siv::PerlinNoise perlin {seed};

    int main() {
        Engine mauve;
        // * Las texturas que vas a cargar
        // TODO Hacer que cargue todas las texturas de un folder (filesystem no compila)
        std::vector<std::string> texturesPaths = {
            "space",
            "videoman",
            "ULTRAKILL"
        };

        try {
            mauve.init(texturesPaths);

            // Chunk thisChunk(glm::vec2(0, 0), perlin);
            // std::cout << "gaming" << '\n';
            // mauve.uploadMeshToEngine(thisChunk.mesh, false);
            // TexturedWorldObject chunk(thisChunk.mesh, mauve.texturedMaterial, 1);

            // chunk.position = glm::vec3(0, 0, 0);

            // int numTex = 0;
            // std::vector<TexturedWorldObject> chunks;
            // int chunksTotal = 1;
            // for (int x = -chunksTotal; x < chunksTotal; x++) {
            //     std::cout << "trabajando en chunk de pos: x-" << x << '\n';
            //     for (int z = -chunksTotal; z < chunksTotal; z++) {
            //         // std::cout << x << '\n';
            //         Chunk thisChunk(glm::vec2(x, z), perlin);
            //         mauve.uploadMeshToEngine(thisChunk.mesh, false);
            //         TexturedWorldObject chunk(thisChunk.mesh, mauve.texturedMaterial, numTex);
            //         numTex == 0 ? numTex = 1 : numTex = 0;

            //         chunk.position = glm::vec3(x * 16, 0, z * 16);
            //         chunks.push_back(chunk);
            //     }
            // }

            // int numTex = 0;
            // std::vector<PointsWorldObject> chunks;
            // int chunksTotal =   2;
            // for (int x = -chunksTotal; x < chunksTotal; x++) {
            //     std::cout << "trabajando en chunk de pos: x-" << x << '\n';
            //     for (int z = -chunksTotal; z < chunksTotal; z++) {
            //         // std::cout << x << '\n';
            //         Chunk thisChunk(glm::vec2(x, z), perlin);
            //         mauve.uploadMeshToEngine(thisChunk.chunkMesh, false);
            //         PointsWorldObject chunk(thisChunk.chunkMesh, mauve.pointsMaterial);
            //         numTex == 0 ? numTex = 1 : numTex = 0;

            //         chunk.position = glm::vec3(x * 16, 0, z * 16);
            //         chunks.push_back(chunk);
            //     }
            // }

            int numTex = 0;
            std::vector<TexturedWorldObject> chunks;
            std::vector<PointsWorldObject> pointChunks;
            int chunksTotal = 1;
            for (int x = -chunksTotal; x < chunksTotal; x++) {
                std::cout << "trabajando en chunk de pos: x-" << x << '\n';
                for (int z = -chunksTotal; z < chunksTotal; z++) {
                    GameChunk thisChunk(glm::vec2(x, z), perlin, true);
                    mauve.uploadMeshToEngine(thisChunk.chunkMesh, false);
                    PointsWorldObject pointsChunk(thisChunk.chunkMesh, mauve.pointsMaterial);

                    GameChunk thatChunk(glm::vec2(x, z), perlin, false);
                    mauve.uploadMeshToEngine(thatChunk.chunkMesh, false);
                    TexturedWorldObject chunk(thatChunk.chunkMesh, mauve.texturedMaterial, 1);

                    chunk.position = glm::vec3(x * 16, 0, z * 16);
                    pointsChunk.position = glm::vec3(x * 16, 0, z * 16);
                    chunks.push_back(chunk);
                    pointChunks.push_back(pointsChunk);
                }
            }


            while (mauve.running) {
                for (int i = 0; i < chunks.size(); i++) {
                    mauve.draw(chunks[i]);
                    mauve.draw(pointChunks[i]);
                }
                // mauve.draw(chunk);
                // mauve.draw(newChunk);

                mauve.render();
            }

            vkDeviceWaitIdle(_device);
            mauve.cleanup();

        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

#else
    #include <iostream>
    #include <vulkan/vulkan.h>

    int main() {
        std::cout << "frick off, man" << std::endl;
        return 0;
    }

#endif