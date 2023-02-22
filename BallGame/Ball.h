#pragma once

#include <glm/glm.hpp>
#include<Vertex.h>

struct Cell;

// POD
struct Ball {
    Ball(float radius, float mass, const glm::vec2& pos,
         const glm::vec2& vel, unsigned int textureId,
         const BasicEngine::Color& color);

    float radius; 
    float mass; 
    glm::vec2 velocity;
    glm::vec2 position;
    unsigned int textureId = 0;
    BasicEngine::Color color;
    Cell* ownerCell = nullptr;
    int cellVectorIndex = -1;
};
