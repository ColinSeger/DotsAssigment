#pragma once
#include "glm/glm.hpp"
#include "../Engine/Constants.h"
#include "../Engine/Components/PhysicsComponent.h"
#include "../Engine/GameObject.h"

class Dot : public GameObject
{
public:

	Dot(float radius, PhysicsComponent* physics, RenderComponent* renderComponent);
	void Update(float deltaTime) override;
	void Render(DotRenderer* render, float deltaTime) override;
	void TakeDamage(int someDamage);
	const int GetHealth(){ return m_health; }

	Dot operator=(const Dot& other){
		physicsComponent->SetPosition(other.physicsComponent->GetPosition());
		this->m_health = other.m_health;
		return *this;
	}
private:

	int m_health;
};

