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
            std::vector<TexturedWorldObject> cosas;

            auto cosaIndices = std::make_shared<Mesh>();

            // std::vector<Vertex> vertices = {
            //     // * atras ./
            //     {{0.5f,  0.5f, -0.5f}, {1, 1, 1},  {0.0f, 0.0f}},
            //     {{0.5f, -0.5f, -0.5f}, {1, 1, 1},  {0.0f, 1.0f}},
            //     {{-0.5f, -0.5f, -0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
            //     {{-0.5f, -0.5f, -0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
            //     {{-0.5f,  0.5f, -0.5f}, {1, 1, 1}, {1.0f, 0.0f}},
            //     {{0.5f,  0.5f, -0.5f}, {1, 1, 1},  {0.0f, 0.0f}},

            //     // * frente ./
            //     {{-0.5f, -0.5f,  0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
            //     {{0.5f, -0.5f,  0.5f}, {1, 1, 1},  {0.0f, 1.0f}},
            //     {{0.5f,  0.5f,  0.5f}, {1, 1, 1},  {0.0f, 0.0f}},
            //     {{0.5f,  0.5f,  0.5f}, {1, 1, 1},  {0.0f, 0.0f}},
            //     {{-0.5f,  0.5f,  0.5f}, {1, 1, 1}, {1.0f, 0.0f}},
            //     {{-0.5f, -0.5f,  0.5f}, {1, 1, 1}, {1.0f, 1.0f}},

            //     // * izquierda ./
            //     {{-0.5f,  0.5f,  0.5f}, {1, 1, 1}, {0.0f, 0.0f}},
            //     {{-0.5f,  0.5f, -0.5f}, {1, 1, 1}, {1.0f, 0.0f}},
            //     {{-0.5f, -0.5f, -0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
            //     {{-0.5f, -0.5f, -0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
            //     {{-0.5f, -0.5f,  0.5f}, {1, 1, 1}, {0.0f, 1.0f}},
            //     {{-0.5f,  0.5f,  0.5f}, {1, 1, 1}, {0.0f, 0.0f}},

            //     // * Derecha ./
            //     {{0.5f, -0.5f, -0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
            //     {{0.5f,  0.5f, -0.5f}, {1, 1, 1}, {1.0f, 0.0f}},
            //     {{0.5f,  0.5f,  0.5f}, {1, 1, 1}, {0.0f, 0.0f}},
            //     {{0.5f,  0.5f,  0.5f}, {1, 1, 1}, {0.0f, 0.0f}},
            //     {{0.5f, -0.5f,  0.5f}, {1, 1, 1}, {0.0f, 1.0f}},
            //     {{0.5f, -0.5f, -0.5f}, {1, 1, 1}, {1.0f, 1.0f}},

            //     // * Abajo ./
            //     {{-0.5f, -0.5f, -0.5f}, {1, 1, 1}, {0.0f, 1.0f}},
            //     {{0.5f, -0.5f, -0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
            //     {{0.5f, -0.5f,  0.5f}, {1, 1, 1}, {1.0f, 0.0f}},
            //     {{0.5f, -0.5f,  0.5f}, {1, 1, 1}, {1.0f, 0.0f}},
            //     {{-0.5f, -0.5f,  0.5f}, {1, 1, 1}, {0.0f, 0.0f}},
            //     {{-0.5f, -0.5f, -0.5f}, {1, 1, 1}, {0.0f, 1.0f}},

            //     // * Arriba ./
            //     {{0.5f,  0.5f, -0.5f}, {1, 1, 1}, {1.0f, 1.0f}},
            //     {{-0.5f,  0.5f, -0.5f}, {1, 1, 1}, {0.0f, 1.0f}},
            //     {{0.5f,  0.5f,  0.5f}, {1, 1, 1}, {1.0f, 0.0f}},
            //     {{-0.5f,  0.5f, -0.5f}, {1, 1, 1}, {0.0f, 1.0f}},
            //     {{-0.5f,  0.5f,  0.5f}, {1, 1, 1}, {0.0f, 0.0f}},
            //     {{0.5f,  0.5f,  0.5f}, {1, 1, 1}, {1.0f, 0.0f}},
            // };

            // cosaIndices->setVertices(vertices);
            // // cosaIndices->indices = indices;
            // mauve.uploadMeshToEngine(cosaIndices, true);
            // TexturedWorldObject cosa(cosaIndices, mauve.texturedMaterial, mauve.texturesNumsMap["videoman"]);

            int chunks = 20;
            for (int x = -chunks; x < chunks; x++) {
                for (int y = -chunks; y < chunks; y++) {
                    // std::cout << x << '\n';
                    Chunk thisChunk(glm::vec2(x, y), perlin);
                    mauve.uploadMeshToEngine(thisChunk.mesh, false);
                    TexturedWorldObject chunk(thisChunk.mesh, mauve.texturedMaterial, mauve.texturesNumsMap["videoman"]);

                    chunk.position = glm::vec3(x * 16, 0, y * 16);
                    cosas.push_back(chunk);
                }
            }

            // // std::cout << x << '\n';
            // Chunk thisChunk(glm::vec2(0, 0), perlin);
            // mauve.uploadMeshToEngine(thisChunk.mesh, false);
            // TexturedWorldObject chunk(thisChunk.mesh, mauve.texturedMaterial, 1);

            // chunk.position = glm::vec3(0, 0, 0);
            // cosas.push_back(chunk);

            while (mauve.running) {
                for (int i = 0; i < cosas.size(); i++) {
                    mauve.draw(cosas[i]);
                }
                // mauve.draw(chunk);
                // mauve.draw(cosa);

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