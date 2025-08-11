#include "../Game/Dot.h"
Dot::Dot(float newRadius, PhysicsComponent* physics)
{
	physicsComponent = physics;
	startPos = physicsComponent->GetPosition();
	physicsComponent->radius = newRadius;

	health = 3;
}

void Dot::Update(float deltaTime)
{
	totalTime += deltaTime;
	if(physicsComponent->damageTaken > 0){
		TakeDamage(physicsComponent->damageTaken);
		physicsComponent->damageTaken = 0;
	}
}

void Dot::Render(DotRenderer* aRenderer, float deltaTime)
{
	float redColor = (glm::cos((totalTime + startPos.x) * 0.1f) * 0.5f + 0.5f) * 255.0f;

	float greenColor = (glm::cos((totalTime + startPos.y) * 0.9f) * 0.5f + 0.5f) * 255.0f;

	float blueColor = (glm::cos(totalTime * 0.4f) * 0.5f + 0.5f) * 255.0f;

	aRenderer->SetDrawColor(redColor, greenColor, blueColor, 255);
	glm::vec2 position = physicsComponent->GetPosition();
	aRenderer->DrawFilledCircle(position.x, position.y, physicsComponent->radius);
}

void Dot::TakeDamage(int someDamage)
{
	health -= someDamage;
}



