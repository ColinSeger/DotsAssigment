#include "../../Engine/Components/RenderComponent.h"

RenderComponent::RenderComponent(DotRenderer* render)
{
    renderer = render;
}

RenderComponent::~RenderComponent()
{

}

void RenderComponent::Render(glm::vec2 position, float radius, double deltaTime)
{
    float redColor = (glm::cos((totalTime + 10) * 0.1f) * 0.5f + 0.5f) * 255.0f;

	float greenColor = (glm::cos((totalTime + 10) * 0.9f) * 0.5f + 0.5f) * 255.0f;

	float blueColor = (glm::cos(totalTime * 0.4f) * 0.5f + 0.5f) * 255.0f;

	renderer->SetDrawColor(redColor, greenColor, blueColor, 255);
	renderer->DrawFilledCircle(position.x, position.y, radius);
}