#pragma once
#include "glm/glm.hpp"
#include "../Engine/Components/PhysicsComponent.h"
#include "../Engine/GameObject.h"

class Dot : public GameObject
{
public:

	Dot(float radius, PhysicsComponent* physics);
	void Update(float deltaTime) override;
	void Render(DotRenderer* render, float deltaTime) override;
	void TakeDamage(int someDamage);

	glm::vec2 startPos;
	glm::vec2 velocity;

	float totalTime = 0;
	float radius = 0;

	int health;

	Dot operator=(const Dot& other){
		physicsComponent->SetPosition(other.physicsComponent->GetPosition());
		this->startPos = other.startPos;
		this->totalTime = other.totalTime;
		this->radius = other.radius;
		this->health = other.health;
		return *this;
	}
private:

	const float DOT_VELOCITY = 50.0f;
};

