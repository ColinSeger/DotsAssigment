#pragma once
#include <vector>
#include <random>
#include <glm/gtc/constants.hpp>
#include <time.h>
#include "glm/glm.hpp"
#include "../../Engine/Constants.h"
// #include "../../Engine/GameObject.h"


class PhysicsComponent
{
public:
    PhysicsComponent();
    PhysicsComponent(glm::vec2 newPosition);
    // PhysicsComponent(glm::vec2 newPosition, GameObject* parentGameObject);
    PhysicsComponent(glm::vec2 newPosition, glm::vec2 startingVelocity);
    ~PhysicsComponent();

    const void SetPosition(glm::vec2 newPosition){ this->position = newPosition; }
    glm::vec2 GetPosition() const{ return this->position; }

    const void SetVelocity(glm::vec2 newVelocity){ this->velocity = newVelocity; }
    glm::vec2 GetVelocity() const{ return this->velocity; }

    // const void SetBound(const int x, const int y){ X_BOUND = x; Y_BOUND = y;}

    const void SetNeighbors(std::vector<PhysicsComponent*> newNeighbors) { neighbors = newNeighbors;};
    std::vector<PhysicsComponent*>& GetNeighbors() { return neighbors; };

    void Update(float deltaTime);
    int damageTaken;
    float radius = 3;
private:
    glm::vec2 position;
    glm::vec2 velocity;
    
    std::vector<PhysicsComponent*> neighbors;
};

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