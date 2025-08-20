#pragma once
#include <vector>
#include <random>
#include <glm/gtc/constants.hpp>
#include <time.h>
#include "glm/glm.hpp"
#include "../../Engine/Constants.h"


class PhysicsComponent
{
public:
    PhysicsComponent();
    PhysicsComponent(glm::vec2 newPosition);
    PhysicsComponent(glm::vec2 newPosition, glm::vec2 startingVelocity);
    ~PhysicsComponent();

    /*Assigns a new position to this physics component*/
    void SetPosition(glm::vec2 newPosition){ this->m_position = newPosition; }
    /*Retrieves a copy of this physics component position*/
    const glm::vec2 GetPosition() const{ return this->m_position; }

    /*Assigns a new velocity to this physics component*/
    void SetVelocity(glm::vec2 newVelocity){ this->m_velocity = newVelocity; }
    /*Retrieves a copy of this physics component*/
    const glm::vec2 GetVelocity() const{ return this->m_velocity; }

    /*Clears this physics components neighbors vector*/
    const void ClearNeighbors(){ m_neighbors.clear(); }
    const void AddNeighbor(PhysicsComponent* newNeighbor) { m_neighbors.push_back(newNeighbor);};
    const void SetNeighbors(std::vector<PhysicsComponent*> newNeighbors) { m_neighbors = newNeighbors;};
    std::vector<PhysicsComponent*>& GetNeighbors() { return m_neighbors; };

    int8_t Update(float deltaTime);

    const void SetRadius(float newRadius){ radius = newRadius; }
    const float GetRadius(){ return radius; }
protected:

    float radius = 3;

private:
    glm::vec2 m_position;
    glm::vec2 m_velocity;
    
    std::vector<PhysicsComponent*> m_neighbors;
};
