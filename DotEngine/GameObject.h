#pragma once
#include "glm/glm.hpp"
#include "DotRenderer.h"

class GameObject
{
    public:
    virtual void Update(float deltaTime);

    virtual void Render(DotRenderer* render, float deltaTime);

    const void SetPosition(glm::vec2 newPosition){
        this->position = newPosition;
    }
    glm::vec2& GetPosition(){
        return this->position;
    }
    std::vector<glm::vec2> neighbors;
    protected:
    glm::vec2 position;
    
};

