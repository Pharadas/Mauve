#pragma once

#include <iostream>
#include <memory>

#include <glm/glm.hpp>
#include <PerlinNoise.hpp>
#include <engine/world_object/world_object.hpp>

class GameChunk {
public:
   GameChunk(glm::vec2 position, siv::PerlinNoise noise, bool puntos);

   std::shared_ptr<Mesh> chunkMesh;
   std::shared_ptr<Mesh> outSideMesh;
   std::shared_ptr<Mesh> inSideMesh;

private:
   std::vector<Vertex> chunkVertices;
   const int chunkSize = 16;
   bool chunkMap[16][256][16];
   int chunkHeight = 256;

   float resolution = 1./chunkSize;

   int cantidadDePuntos = 10000;
};
