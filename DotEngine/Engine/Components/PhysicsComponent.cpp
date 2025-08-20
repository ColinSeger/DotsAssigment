#include "../../Engine/Components/PhysicsComponent.h"

PhysicsComponent::PhysicsComponent()
{
    this->m_position = glm::vec2(10, 10);
    this->m_velocity = glm::vec2(1, 1);
	// this->parentObject = nullptr;
}
PhysicsComponent::PhysicsComponent(glm::vec2 newPosition)
{
    this->m_position = newPosition;

    static std::mt19937 rng(static_cast<unsigned int>(time(nullptr)));
	std::uniform_real_distribution<float> dist(-100.0f, 100.0f);
    this->m_velocity = glm::vec2(dist(rng), dist(rng));

	float angle = dist(rng) * glm::pi<float>() / 100.0f;
	this->m_velocity = glm::vec2(cos(angle), sin(angle));
	// this->parentObject = nullptr;
}

PhysicsComponent::PhysicsComponent(glm::vec2 newPosition, glm::vec2 startingVelocity)
{
    this->m_position = newPosition;
    this->m_velocity = startingVelocity;
	// this->parentObject = nullptr;
}

PhysicsComponent::~PhysicsComponent()
{
}

int8_t PhysicsComponent::Update(float deltaTime)
{
	int8_t result = 0;
    for(auto& neighbor : m_neighbors){
		glm::vec2 neighborPosition = neighbor->GetPosition();
	 	if(neighborPosition == m_position) continue;
        
		float dx = m_position.x - neighborPosition.x;
		float dy = m_position.y - neighborPosition.y;
		float vx = neighbor->GetVelocity().x - m_velocity.x;
		float vy = neighbor->GetVelocity().y - m_velocity.y;
		float dot = dx * vx + dy * vy;
		if(dot < 0) continue;
		glm::vec2 normal = glm::normalize(m_position - neighborPosition);

		this->m_velocity = glm::reflect(m_velocity, normal);
		// neighbor->SetVelocity(glm::reflect(neighbor->GetVelocity(), -normal));
		result++;
		radius++;	
	}
	m_neighbors.clear();
    m_position += m_velocity * 50.f * deltaTime;

	if (m_position.x - radius < 0.0f)
	{
		m_position.x = radius;
		m_velocity.x *= -1;
	}
	else if (m_position.x + radius > SCREEN_WIDTH)
	{
		m_position.x = SCREEN_WIDTH - radius;
		m_velocity.x *= -1;
	}

	if (m_position.y - radius < 0.0f)
	{
		m_position.y = radius;
		m_velocity.y *= -1;
	}
	else if (m_position.y + radius > SCREEN_HEIGHT)
	{
		m_position.y = SCREEN_HEIGHT - radius;
		m_velocity.y *= -1;
	}
	return result;
}