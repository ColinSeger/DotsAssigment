#pragma once
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "glm/glm.hpp"
#include "../Engine/Components/PhysicsComponent.h"
#include "../Engine/Components/RenderComponent.h"
#include "../Engine/GameObject.h"
#include "../Engine/QuadTree.h"
#include "../Engine/DotRenderer.h"
#include "../Game/Dot.h"

static const int SCREEN_WIDTH = 1920;
static const int SCREEN_HEIGHT = 1080;
static const glm::vec2 SCREEN_CENTRE = {SCREEN_WIDTH /2, SCREEN_HEIGHT / 2};

enum class DebugDrawMode : uint8_t{
    None,
    Quad,
    Dots,
    Both
};
static const DebugDrawMode debugMode = DebugDrawMode::None;

class Game
{
public:
	Game(DotRenderer* aRenderer);

	void Init();

	void Start();

	int Update(float deltaTime);

	void Render(float deltaTime);

	void CleanUp();

	float GetTime(){return currentTime;}
private:
	const int DOT_AMOUNT = 2000;	

	DotRenderer* renderer;
	QuadTree* quadTree = nullptr;
	std::vector<Dot> dots;
	std::vector<PhysicsComponent> physicsComponents;
	std::vector<RenderComponent> renderComponents;

	float currentTime = 0;

};

