#pragma once
#include "glm/glm.hpp"
#include "../../Engine/DotRenderer.h"

class RenderComponent
{
public:
    RenderComponent(DotRenderer* render);
    ~RenderComponent();

    void Render(const glm::vec2 position, const float radius, const double deltaTime);
    const void SetStartPos(glm::vec2 newStartPos){ m_startPosition = newStartPos;}
    const void Reset(){ m_lifetime = 0; }
private:
    float m_lifetime;
    glm::vec2 m_startPosition;
    DotRenderer* m_renderPointer;
};
