#include "Dot.h"
static const int SCREEN_WIDTH = 1000;
static const int SCREEN_HEIGHT = 800;
Dot::Dot(glm::vec2 aPosition, float aRadius)
{
	position = aPosition;
	startPos = aPosition;
	radius = aRadius;

	static std::mt19937 rng(static_cast<unsigned int>(time(nullptr)));
	std::uniform_real_distribution<float> dist(-100.0f, 100.0f);

	velocity = glm::vec2(dist(rng), dist(rng));

	float angle = dist(rng) * glm::pi<float>() / 100.0f;
	velocity = glm::vec2(cos(angle), sin(angle));

	health = 3;
}

void Dot::Render(DotRenderer* aRenderer, float dt)
{
	totalTime += dt;

	position += velocity * DOT_VELOCITY * dt;

	if (!overriden)
	{

		float redColor = (glm::cos((totalTime + startPos.x) * 0.1f) * 0.5f + 0.5f) * 255.0f;

		float greenColor = (glm::cos((totalTime + startPos.y) * 0.9f) * 0.5f + 0.5f) * 255.0f;

		float blueColor = (glm::cos(totalTime * 0.4f) * 0.5f + 0.5f) * 255.0f;

		aRenderer->SetDrawColor(redColor, greenColor, blueColor, 255);
	}
	else 
	{
		aRenderer->SetDrawColor(255, 255, 255, 255);
	}

	aRenderer->DrawFilledCircle(position.x, position.y, radius);

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

void Dot::TakeDamage(int someDamage)
{
	health -= someDamage;
}



