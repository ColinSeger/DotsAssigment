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

	float GetTime(){return m_currentTime;}
private:
	const unsigned int DOT_AMOUNT = 10000;	

	DotRenderer* m_renderer = nullptr;
	QuadTree* m_quadTree = nullptr;
	SwapTree* m_swapTree = nullptr;
	
	std::vector<Dot> m_dots;
	std::vector<PhysicsComponent> m_physicsComponents;
	std::vector<RenderComponent> m_renderComponents;

	float m_currentTime = 0;

};

