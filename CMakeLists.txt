cmake_minimum_required(VERSION 3.10)

project("Mauve")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

INCLUDE_DIRECTORIES(include/)
INCLUDE_DIRECTORIES(include/game/)
INCLUDE_DIRECTORIES(include/engine/)
INCLUDE_DIRECTORIES(include/engine/device/)
INCLUDE_DIRECTORIES(include/engine/window/)
INCLUDE_DIRECTORIES(include/engine/pipeline/)
INCLUDE_DIRECTORIES(include/engine/descriptors/)
INCLUDE_DIRECTORIES(include/engine/texture/)
INCLUDE_DIRECTORIES(include/engine/material/)
INCLUDE_DIRECTORIES(include/engine/mesh/)
INCLUDE_DIRECTORIES(include/engine/world_object/)

file(GLOB SOURCES "*/.cpp"
				  "source/*.cpp"
				  "include/game/*.cpp"
				  "include/engine/*.cpp"
				  "include/engine/device/*.cpp"
				  "include/engine/window/*.cpp"
				  "include/engine/pipeline/*.cpp"
				  "include/engine/descriptors/*.cpp"
				  "include/engine/texture/*.cpp"
				  "include/engine/mesh/*.cpp"
				  "include/engine/world_object/*.cpp"
				  "include/engine/material/*.cpp")

# set(CMAKE_BUILD_TYPE Release)
set (CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS_RELEASE "-O3")

LINK_DIRECTORIES(lib/)

add_executable("${PROJECT_NAME}" "${SOURCES}")

TARGET_LINK_LIBRARIES(Mauve glfw)
TARGET_LINK_LIBRARIES(Mauve vulkan)
TARGET_LINK_LIBRARIES(Mauve tinyobjloader)
