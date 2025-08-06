#pragma once
#include <vector>
#include "glm/glm.hpp"
// #include "QuadTree.h"
#include "DotRenderer.h"
#include "GameObject.h"
#include "Dot.h"
#include <cstdlib>
#include <algorithm>

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
	const int DOT_AMOUNT = 500;	

	DotRenderer* renderer;
	std::vector<Dot> dots;

	float currentTime = 0;
};

