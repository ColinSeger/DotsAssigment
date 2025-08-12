#pragma once
#include "glm/glm.hpp"
#include "../Engine/DotRenderer.h"
#include "../Engine/Components/PhysicsComponent.h"
#include "../Engine/Components/RenderComponent.h"

class GameObject
{
    public:
    virtual void Update(float deltaTime);

    virtual void Render(DotRenderer* render, float deltaTime);
    PhysicsComponent* physicsComponent;
    RenderComponent* renderComponent;
    protected:
    
};

