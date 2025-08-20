#include "../../Engine/Components/RenderComponent.h"

RenderComponent::RenderComponent(DotRenderer* render)
{
    m_renderPointer = render;
}

RenderComponent::~RenderComponent()
{

}

void RenderComponent::Render(const glm::vec2 position, const float radius, const double deltaTime)
{
    m_lifetime += deltaTime;
    int redColor = (glm::cos((m_lifetime + m_startPosition.x) * 0.1f) * 0.5f + 0.5f) * 255.0f;

	int greenColor = (glm::cos((m_lifetime + m_startPosition.y) * 0.9f) * 0.5f + 0.5f) * 255.0f;

	int blueColor = (glm::cos(m_lifetime * 0.4f) * 0.5f + 0.5f) * 255.0f;
	
	uint32_t color = ((255 & 0xff) << 24) + ((redColor & 0xff) << 16) + ((greenColor & 0xff) << 8) + (blueColor & 0xff);
	
	m_renderPointer->DrawFilledCircle(position.x, position.y, radius, color);
}