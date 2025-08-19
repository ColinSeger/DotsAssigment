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
    // PhysicsComponent(glm::vec2 newPosition, GameObject* parentGameObject);
    PhysicsComponent(glm::vec2 newPosition, glm::vec2 startingVelocity);
    ~PhysicsComponent();

    void SetPosition(glm::vec2 newPosition){ this->m_position = newPosition; }
    const glm::vec2 GetPosition() const{ return this->m_position; }

    void SetVelocity(glm::vec2 newVelocity){ this->m_velocity = newVelocity; }
    const glm::vec2 GetVelocity() const{ return this->m_velocity; }

    // const void SetBound(const int x, const int y){ X_BOUND = x; Y_BOUND = y;}
    const void ClearNeighbors(){ m_neighbors.clear(); }
    const void AddNeighbor(PhysicsComponent* newNeighbor) { m_neighbors.push_back(newNeighbor);};
    const void SetNeighbors(std::vector<PhysicsComponent*> newNeighbors) { m_neighbors = newNeighbors;};
    std::vector<PhysicsComponent*>& GetNeighbors() { return m_neighbors; };

    uint8_t Update(float deltaTime);

    const void SetRadius(float newRadius){ radius = newRadius; }
    const float GetRadius(){ return radius; }
protected:

    float radius = 3;

private:
    glm::vec2 m_position;
    glm::vec2 m_velocity;
    
    std::vector<PhysicsComponent*> m_neighbors;
};
/*
class ObjectBoundingBox
{
public:
    ObjectBoundingBox(){
        position = 0;
        width = 0;
        // height = 0;
    }
    ObjectBoundingBox(glm::vec2 parentPosition, float parentSize){
        position = &parentPosition;
        width = parentSize;
        // height = parentSize;
    }
    ObjectBoundingBox(glm::vec2* parentPosition, float parentSize){
        position = parentPosition;
        width = parentSize;
        // height = parentSize;
    }
    ObjectBoundingBox(glm::vec2 parentPosition, float parentHeight, float parentWidth){
        position = &parentPosition;
        width = parentWidth;
        // height = parentHeight;
    }
    const glm::vec2 UpperLeft()
    {
        return *position - width;
    }
    const glm::vec2 BottomRight()
    {
        glm::vec2 returnValue = *position - width;
        return returnValue;
    }

    bool InBounds(float xPos, float yPos){
        return InBounds({xPos, yPos});
    }
    bool InBounds(glm::vec2 position){
        float xAxis = position.x + width;
        float yAxis = position.y + width;
        if(position.x >= -xAxis && position.x <= xAxis
            && position.y >= -yAxis && position.y <= yAxis){
            return true;
        }
        return false;
    }

private:
    glm::vec2* position;
    float width = 10.f;
    // float height = 10.f;
};
*/