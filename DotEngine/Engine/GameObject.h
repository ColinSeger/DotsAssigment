#pragma once
#include "glm/glm.hpp"
#include "../Engine/DotRenderer.h"
#include "../Engine/Components/PhysicsComponent.h"

class GameObject
{
    public:
    virtual void Update(float deltaTime);

    virtual void Render(DotRenderer* render, float deltaTime);
    PhysicsComponent* physicsComponent;
    protected:
    
};

