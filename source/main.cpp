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
        };

        try {
            mauve.init(texturesPaths);
            std::vector<TexturedWorldObject> cosas;
            int chunks = 3;

            for (int x = -chunks; x < chunks; x++) {
                for (int y = -chunks; y < chunks; y++) {
                    // std::cout << x << '\n';
                    Chunk thisChunk(glm::vec2(x, y), perlin);
                    mauve.uploadMeshToEngine(thisChunk.mesh);
                    TexturedWorldObject chunk(thisChunk.mesh, mauve.texturedMaterial, 1);

                    chunk.position = glm::vec3(x * 16, 0, y * 16);
                    cosas.push_back(chunk);
                }
            }

            while (mauve.running) {
                for (int i = 0; i < cosas.size(); i++) {
                    mauve.draw(cosas[i]);
                }

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