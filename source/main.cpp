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

            mauve.uploadMeshToEngine(icosahedro, false);

            // WorldObject objeto(icosahedro, mauve.defaultMaterial);

            TexturedWorldObject objetoConTextura(icosahedro, mauve.texturedMaterial, 0);

            // int numTex = 0;
            // std::vector<TexturedWorldObject> chunks;
            // // std::vector<WorldObject> chunks;
            // // std::vector<PointsWorldObject> pointChunks;
            // int chunksTotal = 10;
            // for (int x = -chunksTotal; x < chunksTotal; x++) {
            //     for (int z = -chunksTotal; z < chunksTotal; z++) {
            //         // std::cout << "trabajando en chunk de pos: x = " << x << " z = " << z << "           \r";

            //         // GameChunk thatChunk(glm::vec2(x, z), perlin, false);
            //         // mauve.uploadMeshToEngine(thatChunk.chunkMesh, false);

            //         // TexturedWorldObject chunk(thatChunk.chunkMesh, mauve.texturedMaterial, 1);
            //         // chunk.position = glm::vec3(x * 16, 0, z * 16);
            //         // chunks.push_back(chunk);
            //         // // WorldObject chunk(thatChunk.chunkMesh, mauve.defaultMaterial);

            //         // // pointsChunk.position = glm::vec3(x * 16, 0, z * 16);
            //         // // chunks.push_back(chunk);
            //         // // pointChunks.push_back(pointsChunk);
            //         TexturedWorldObject cosa(icosahedro, mauve.texturedMaterial, 1);
            //         cosa.position = glm::vec3(x, 0, z);
            //         chunks.push_back(cosa);
            //     }
            // }

            // // std::cout << '\n' << "Cantidad de puntos total: " << 2 * pow(chunksTotal, 2) * 10000 << '\n';
            // // chunks[0].position += glm::vec3(0, 0, 100);
            // objeto.position = glm::vec3(0, 0, 0);

            // int counter = 0;
            while (mauve.running) {
                // mauve.draw(objeto);
                // for (int i = 0; i < chunks.size(); i++) {
                //     mauve.draw(chunks[i]);
                //     // mauve.draw(pointChunks[i]);
                // }
                mauve.draw(objetoConTextura);

                // if (counter > 100) {
                //     int cosa = 0;
                //     std::cout << "Changing texture of chunk: " << cosa << '\n';
                //     chunks[cosa].texture = (chunks[cosa].texture + 1) % 3;
                //     counter = 0;
                // }

                // mauve.draw(chunk);
                // mauve.draw(newChunk);
                // mauve.draw(objeto);
                // mauve.draw(objetoConTextura);

                // counter++;
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

    int.texturedMaterial, 1() {
        std::cout << "frick off, man" << std::endl;
        return 0;
    }

#endif