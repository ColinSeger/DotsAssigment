#pragma once
#include "glm/glm.hpp"
#include "../../Engine/DotRenderer.h"

class RenderComponent
{
public:
    RenderComponent(DotRenderer* render);
    ~RenderComponent();

    void Render(glm::vec2 position, float radius, double deltaTime);
    const void SetStartPos(glm::vec2 newStartPos){ startPos = newStartPos;}
    const void Reset(){ totalTime = 0; }
private:
    float totalTime;
    glm::vec2 startPos;
    DotRenderer* renderer;
};
