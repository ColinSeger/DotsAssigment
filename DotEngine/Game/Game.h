#pragma once
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "glm/glm.hpp"
#include "../Engine/Components/PhysicsComponent.h"
#include "../Engine/GameObject.h"
#include "../Engine/QuadTree.h"
#include "../Engine/DotRenderer.h"
#include "../Game/Dot.h"

static const int SCREEN_WIDTH = 1000;
static const int SCREEN_HEIGHT = 800;

class Game
{
public:
	Game(DotRenderer* aRenderer);
	void Update(float aDeltaTime);

	void Render(float deltaTime);

	void CleanUp();

	float GetTime(){return currentTime;}
private:
	const int DOT_AMOUNT = 1000;	

	DotRenderer* renderer;
	std::vector<Dot> dots;
	std::vector<PhysicsComponent> physicsComponents;

	float currentTime = 0;

};

