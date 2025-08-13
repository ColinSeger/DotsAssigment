#include "../../Engine/Components/PhysicsComponent.h"

PhysicsComponent::PhysicsComponent()
{
    this->position = glm::vec2(10, 10);
    this->velocity = glm::vec2(1, 1);
	// this->parentObject = nullptr;
}
PhysicsComponent::PhysicsComponent(glm::vec2 newPosition)
{
    this->position = newPosition;

    static std::mt19937 rng(static_cast<unsigned int>(time(nullptr)));
	std::uniform_real_distribution<float> dist(-100.0f, 100.0f);
    this->velocity = glm::vec2(dist(rng), dist(rng));

	float angle = dist(rng) * glm::pi<float>() / 100.0f;
	this->velocity = glm::vec2(cos(angle), sin(angle));
	// this->parentObject = nullptr;
}
// PhysicsComponent::PhysicsComponent(glm::vec2 newPosition, GameObject* parentGameObject)
// {
//     this->position = newPosition;
// 	// this->parentObject = parentGameObject;

//     static std::mt19937 rng(static_cast<unsigned int>(time(nullptr)));
// 	std::uniform_real_distribution<float> dist(-100.0f, 100.0f);
//     this->velocity = glm::vec2(dist(rng), dist(rng));

// 	float angle = dist(rng) * glm::pi<float>() / 100.0f;
// 	this->velocity = glm::vec2(cos(angle), sin(angle));
// }
PhysicsComponent::PhysicsComponent(glm::vec2 newPosition, glm::vec2 startingVelocity)
{
    this->position = newPosition;
    this->velocity = startingVelocity;
	// this->parentObject = nullptr;
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::Update(float deltaTime)
{    
    for(auto& neighbor : neighbors){
        // break;
	 	if(neighbor->GetPosition() == position) continue;
        glm::vec2 neighborPosition = neighbor->GetPosition();
	 	float dist = glm::distance(position, neighborPosition);
	 	float minDist = radius + neighbor->radius;
	 	if (dist < minDist)
	 	{
            float dx = position.x - neighbor->GetPosition().x;
            float dy = position.y - neighbor->GetPosition().y;
            float vx = neighbor->GetVelocity().x - velocity.x;
            float vy = neighbor->GetVelocity().y - velocity.y;
            float dot = dx * vx + dy * vy;
            if(dot < 0) continue;
	 		glm::vec2 normal = glm::normalize(position - neighborPosition);

	 		this->velocity = glm::reflect(velocity, normal);
	 		neighbor->SetVelocity(glm::reflect(neighbor->GetVelocity(), -normal));
			// for (int i = 0; i < neighbor->neighbors.size(); neighbor->neighbors)
			// {
			// 	if(neighbor->neighbors[i] == this){
			// 		neighbor->neighbors.erase(neighbor->neighbors.begin() + i);				
			// 	}
			// }
			
			damageTaken+=1;
			radius++;
		}		
	}
    position += velocity * 50.f * deltaTime;

	if (position.x - radius < 0.0f)
	{
		position.x = radius;
		velocity.x *= -1;
	}
	else if (position.x + radius > X_BOUND)
	{
		position.x = X_BOUND - radius;
		velocity.x *= -1;
	}

	if (position.y - radius < 0.0f)
	{
		position.y = radius;
		velocity.y *= -1;
	}
	else if (position.y + radius > Y_BOUND)
	{
		position.y = Y_BOUND - radius;
		velocity.y *= -1;
	}
}