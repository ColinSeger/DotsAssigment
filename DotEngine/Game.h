#pragma once
#include "vector"
#include "DotRenderer.h"
#include "Dot.h"
#include <cstdlib>
#include "glm/glm.hpp"
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
private:
	const int DOT_AMOUNT = 100;	

	DotRenderer* renderer;
	std::vector<Dot*> dots;
};

