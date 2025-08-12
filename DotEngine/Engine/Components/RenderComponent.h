#pragma once
#include "glm/glm.hpp"
#include "../../Engine/DotRenderer.h"

class RenderComponent
{
public:
    RenderComponent(DotRenderer* render);
    ~RenderComponent();

    void Render(glm::vec2 position, float radius, double deltaTime);
    const void Reset(){ totalTime = 0; }
private:
    // glm::vec2 startPos;
    float totalTime;
    DotRenderer* renderer;
};
