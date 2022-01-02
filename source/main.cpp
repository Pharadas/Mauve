// #define REBUILD_PROJECT

#ifndef REBUILD_PROJECT
    #include <vulkan/vulkan.h>
    #include <engine/engine.hpp>

    #include <iostream>
    #include <string>
    #include <stdexcept>
    #include <cstdlib>

    int main() {
        Engine engine;

        try {
            engine.run();
        } catch (const std::exception& e) {
            // std::cerr << e.what() << std::endl;
            std::cout << "gaming";
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