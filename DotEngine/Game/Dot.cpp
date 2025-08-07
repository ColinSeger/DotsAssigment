#include "../Game/Dot.h"
static const int SCREEN_WIDTH = 1000;
static const int SCREEN_HEIGHT = 800;
Dot::Dot(glm::vec2 position, float aRadius)
{
	this->SetPosition(position);
	startPos = position;
	radius = aRadius;

	static std::mt19937 rng(static_cast<unsigned int>(time(nullptr)));
	std::uniform_real_distribution<float> dist(-100.0f, 100.0f);

	velocity = glm::vec2(dist(rng), dist(rng));

	float angle = dist(rng) * glm::pi<float>() / 100.0f;
	velocity = glm::vec2(cos(angle), sin(angle));

	health = 3;
}

void Dot::Update(float deltaTime){
	
	for(glm::vec2 neighbor : neighbors){
		if(neighbor == position) continue;
		float dist = glm::distance(GetPosition(), neighbor);
		float minDist = radius + radius;
		if (dist < minDist && dist > 0.001f)
		{
			glm::vec2 normal = glm::normalize(position - neighbor);

			velocity = glm::reflect(velocity, normal);
			// dotTwo.velocity = glm::reflect(dotTwo.velocity, -normal);

			float overlap1 = 1.5f * ((minDist + 1) - dist);
			float overlap2 = 1.5f * (minDist - dist);
			// SetPosition((GetPosition() - normal * overlap1));
			// dotTwo.SetPosition((.GetPosition() - normal * overlap2));
			// TakeDamage(1);
			// radius++;
		}		
	}
	totalTime += deltaTime;

	position += velocity * DOT_VELOCITY * deltaTime;

	if (position.x - radius < 0.0f)
	{
		position.x = radius;
		velocity.x *= -1;
	}
	else if (position.x + radius > SCREEN_WIDTH)
	{
		position.x = SCREEN_WIDTH - radius;
		velocity.x *= -1;
	}

	if (position.y - radius < 0.0f)
	{
		position.y = radius;
		velocity.y *= -1;
	}
	else if (position.y + radius > SCREEN_HEIGHT)
	{
		position.y = SCREEN_HEIGHT - radius;
		velocity.y *= -1;
	}
}

void Dot::Render(DotRenderer* aRenderer, float deltaTime)
{
	float redColor = (glm::cos((totalTime + startPos.x) * 0.1f) * 0.5f + 0.5f) * 255.0f;

	float greenColor = (glm::cos((totalTime + startPos.y) * 0.9f) * 0.5f + 0.5f) * 255.0f;

	float blueColor = (glm::cos(totalTime * 0.4f) * 0.5f + 0.5f) * 255.0f;

	aRenderer->SetDrawColor(redColor, greenColor, blueColor, 255);

	aRenderer->DrawFilledCircle(position.x, position.y, radius);
}

void Dot::TakeDamage(int someDamage)
{
	health -= someDamage;
}



