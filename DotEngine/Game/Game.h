#pragma once
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "glm/glm.hpp"
#include "../Engine/QuadTree.h"
#include "../Engine/DotRenderer.h"
#include "../Engine/GameObject.h"
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
	const int DOT_AMOUNT = 2000;	

	DotRenderer* renderer;
	std::vector<Dot> dots;

	float currentTime = 0;

};

