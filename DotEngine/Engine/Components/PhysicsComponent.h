#pragma once
#include <vector>
#include "glm/glm.hpp"

class PhysicsComponent
{
public:
    PhysicsComponent();
    PhysicsComponent(glm::vec2 newPosition);
    ~PhysicsComponent();

    const void SetPosition(glm::vec2 newPosition){ this->position = newPosition; }
    glm::vec2 GetPosition() const{ return this->position; }

private:
    glm::vec2 position;
    glm::vec2 velocity;

    std::vector<PhysicsComponent*> neighbors;
};

class oundingBox
{
    oundingBox(glm::vec2* parentPosition, float parentSize){
        position = parentPosition;
        size = parentSize;
    }

    glm::vec2* position;
    float size;
};