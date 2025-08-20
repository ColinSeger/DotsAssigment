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
    const unsigned int GetId(){ return id; }

    const void SetPosition(glm::vec2 newPosition){ this->m_physicsComponent->SetPosition(newPosition); }
    const glm::vec2 GetPosition(){ return this->m_physicsComponent->GetPosition(); }

    RenderComponent* GetRenderComponent(){ return m_renderComponent; }
    
    protected:
    unsigned int id;
    PhysicsComponent* m_physicsComponent;
    
    RenderComponent* m_renderComponent;
};

