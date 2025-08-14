#pragma once
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "glm/glm.hpp"
#include "../Engine/Constants.h"
#include "../Engine/Components/PhysicsComponent.h"
#include "../Engine/Components/RenderComponent.h"
#include "../Engine/GameObject.h"
#include "../Engine/QuadTree.h"
#include "../Engine/QuadSwapChainTest/SwapTree.h"
#include "../Engine/DotRenderer.h"
#include "../Game/Dot.h"

class Game
{
public:
	Game(DotRenderer* aRenderer);

	void Init();

	int Update(float deltaTime);

	void Render(float deltaTime);

	void CleanUp();

	float GetTime(){return currentTime;}
private:
	const int DOT_AMOUNT = 1000;	

	DotRenderer* renderer;
	QuadTree* quadTree = nullptr;
	SwapTree* swapTree = nullptr;
	
	std::vector<Dot> dots;
	std::vector<PhysicsComponent> physicsComponents;
	std::vector<RenderComponent> renderComponents;

	float currentTime = 0;

};

