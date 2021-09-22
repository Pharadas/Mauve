cmake_minimum_required(VERSION 3.10)

project("GamingTime")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

INCLUDE_DIRECTORIES(include/)
INCLUDE_DIRECTORIES(include/engine/)
INCLUDE_DIRECTORIES(include/engine/window/)
INCLUDE_DIRECTORIES(include/engine/device/)

file(GLOB SOURCES "*/.cpp"
				  "source/*.cpp"
				  "include/engine/*.cpp"
				  "include/engine/window/*.cpp"
				  "include/engine/device/*.cpp")

set (CMAKE_CXX_STANDARD 17)

LINK_DIRECTORIES(lib/)

add_executable("${PROJECT_NAME}" "${SOURCES}")

TARGET_LINK_LIBRARIES(GamingTime libglfw3.a)
TARGET_LINK_LIBRARIES(GamingTime vulkan-1.lib)
TARGET_LINK_LIBRARIES(GamingTime tinyobjloader.a)
