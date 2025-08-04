#pragma once
#include "glm/glm.hpp"
#include "DotRenderer.h"
#include <random>
#include <glm/gtc/constants.hpp>
#include <time.h>

class Dot
{
public:

	Dot(glm::vec2 aPosition, float aRadius);
	void Render(DotRenderer* aRenderer, float dt);
	void TakeDamage(int someDamage);

	glm::vec2 position;
	glm::vec2 startPos;
	glm::vec2 velocity;

	float totalTime = 0;
	float radius = 0;

	int health;

	bool overriden = false;

	bool operator==(Dot const* f)
	{
		if(this == f){
			return true;
		}
		return false;
	}
	bool operator!=(Dot const* f)
	{
		if(this != f){
			return false;
		}
		return true;
	}
private:

	const float DOT_VELOCITY = 50.0f;
};

