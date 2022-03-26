#pragma once

#include <iostream>
#include <memory>

#include <glm/glm.hpp>
#include <PerlinNoise.hpp>
#include <engine/world_object/world_object.hpp>

class Chunk {
public:
   Chunk(glm::vec2 position, siv::PerlinNoise noise);

   std::shared_ptr<Mesh> mesh;

private:
   std::vector<Vertex> chunkVertices;
   const int chunkSize = 16;
   bool chunkMap[16][256][16];
   int chunkHeight = 256;

   float resolution = 1./chunkSize;
};
