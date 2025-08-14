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
    totalTime += deltaTime;
    int redColor = (glm::cos((totalTime + startPos.x) * 0.1f) * 0.5f + 0.5f) * 255.0f;

	int greenColor = (glm::cos((totalTime + startPos.y) * 0.9f) * 0.5f + 0.5f) * 255.0f;

	int blueColor = (glm::cos(totalTime * 0.4f) * 0.5f + 0.5f) * 255.0f;
	
	uint32_t color = ((255 & 0xff) << 24) + ((redColor & 0xff) << 16) + ((greenColor & 0xff) << 8)
		+ (blueColor & 0xff);
	renderer->DrawFilledCircle(position.x, position.y, radius, color);
}