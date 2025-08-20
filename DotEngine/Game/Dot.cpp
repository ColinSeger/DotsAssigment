#include "../Game/Dot.h"
Dot::Dot(unsigned int newID, float newRadius, PhysicsComponent* physics, RenderComponent* render)
{
	physicsComponent = physics;
	physicsComponent->SetRadius(newRadius);
	renderComponent = render;
	renderComponent->Reset();
	id = newID;
	m_health = 3;
}

void Dot::Update(float deltaTime)
{
	TakeDamage(physicsComponent->Update(deltaTime));
}

void Dot::TakeDamage(const int8_t someDamage)
{
	m_health -= someDamage;
}



