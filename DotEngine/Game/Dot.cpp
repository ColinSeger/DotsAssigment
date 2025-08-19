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
	uint8_t damage = physicsComponent->Update(deltaTime);
	if(damage > 0){
		TakeDamage(damage);
	}
}

void Dot::TakeDamage(const int someDamage)
{
	m_health -= someDamage;
}



