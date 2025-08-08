#include "../../Engine/Components/PhysicsComponent.h"

PhysicsComponent::PhysicsComponent()
{
    this->position = glm::vec2(10, 10);
    this->velocity = glm::vec2(1, 1);
}
PhysicsComponent::PhysicsComponent(glm::vec2 newPosition)
{
    this->position = newPosition;
    this->velocity = glm::vec2(1, 1);
}

PhysicsComponent::~PhysicsComponent()
{
}

