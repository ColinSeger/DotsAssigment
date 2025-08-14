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
	int health;

	Dot operator=(const Dot& other){
		physicsComponent->SetPosition(other.physicsComponent->GetPosition());
		this->health = other.health;
		return *this;
	}
private:

	
};

