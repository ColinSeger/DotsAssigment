#pragma once
#include "glm/glm.hpp"
#include "../Engine/Constants.h"
#include "../Engine/Components/PhysicsComponent.h"
#include "../Engine/GameObject.h"

class Dot : public GameObject
{
public:

	Dot(unsigned int newID, float radius, PhysicsComponent* physics, RenderComponent* renderComponent);
	void Update(float deltaTime) override;
	void TakeDamage(const int someDamage);

	/*Returns the amount of health on this dot*/
	const int GetHealth(){ return m_health; }

	Dot operator=(const Dot& other){
		m_physicsComponent->SetPosition(other.m_physicsComponent->GetPosition());
		this->m_health = other.m_health;
		this->id = other.id;
		this->m_physicsComponent = other.m_physicsComponent;
		this->m_renderComponent = other.m_renderComponent;
		return *this;
	}
private:
	int m_health = 0;
};

