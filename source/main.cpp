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

	// // Noise
	// const siv::PerlinNoise::seed_type seed = 2912929u;
	// const siv::PerlinNoise perlin {seed};

    int main() {
        Engine mauve;

        try {
            mauve.init();

            std::shared_ptr<Mesh> icosahedro(std::make_shared<Mesh>());

            float phi = (1.0f + sqrt(5.0f)) * 0.5f; // golden ratio
            float a = 1.0f;
            float b = 1.0f / phi;

            // add vertices
            auto v1  = glm::vec3(0, b, -a);
            auto v2  = glm::vec3(b, a, 0);
            auto v3  = glm::vec3(-b, a, 0);
            auto v4  = glm::vec3(0, b, a);
            auto v5  = glm::vec3(0, -b, a);
            auto v6  = glm::vec3(-a, 0, b);
            auto v7  = glm::vec3(0, -b, -a);
            auto v8  = glm::vec3(a, 0, -b);
            auto v9  = glm::vec3(a, 0, b);
            auto v10 = glm::vec3(-a, 0, -b);
            auto v11 = glm::vec3(b, -a, 0);
            auto v12 = glm::vec3(-b, -a, 0);

            icosahedro->addTriangle(v3, v2, v1);
            icosahedro->addTriangle(v2, v3, v4);
            icosahedro->addTriangle(v6, v5, v4);
            icosahedro->addTriangle(v5, v9, v4);
            icosahedro->addTriangle(v8, v7, v1);
            icosahedro->addTriangle(v7, v10, v1);
            icosahedro->addTriangle(v12, v11, v5);
            icosahedro->addTriangle(v11, v12, v7);
            icosahedro->addTriangle(v10, v6, v3);
            icosahedro->addTriangle(v6, v10, v12);
            icosahedro->addTriangle(v9, v8, v2);
            icosahedro->addTriangle(v8, v9, v11);
            icosahedro->addTriangle(v3, v6, v4);
            icosahedro->addTriangle(v9, v2, v4);
            icosahedro->addTriangle(v10, v3, v1);
            icosahedro->addTriangle(v2, v8, v1);
            icosahedro->addTriangle(v12, v10, v7);
            icosahedro->addTriangle(v8, v11, v7);
            icosahedro->addTriangle(v6, v12, v5);
            icosahedro->addTriangle(v11, v9, v5);

            mauve.uploadMeshToEngine(icosahedro);

            WorldObject objeto(icosahedro, mauve.defaultMaterial);
            WorldObject cosa(icosahedro, mauve.defaultMaterial);
            cosa.position = glm::vec3(1, 1, 1);
            objeto.position = glm::vec3(0, 0, 0);

            while (mauve.running) {
                mauve.objectsToDraw.push_back(&objeto);
                mauve.objectsToDraw.push_back(&cosa);
                mauve.draw();
            }

            vkDeviceWaitIdle(_device);
            icosahedro.get()->cleanup();
            mauve.cleanup();

        } catch (const std::exception& e) {
            // std::cerr << e.what() << std::endl;
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