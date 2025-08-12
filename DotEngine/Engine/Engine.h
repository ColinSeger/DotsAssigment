#pragma once
#include "../Engine/DotRenderer.h"
#include "../Game/Game.h"
#include <chrono>
#include <future>

// static const int SCREEN_WIDTH = 1000;
// static const int SCREEN_HEIGHT = 800;
// static const glm::vec2 SCREEN_CENTRE = {SCREEN_WIDTH /2, SCREEN_HEIGHT / 2};

class Engine
{
public:
    Engine();
    ~Engine();

    int Validate();

    int StartGame();

    const Game* GetGameManager(){ return gameManager; }

    DotRenderer* GetRender(){ return renderer; }

private:

    void Tick();
    void PhysicsTick();
    void FpsCounter(double fps);
    void DebugText(std::string text, int offset, double fps);

    DotRenderer* renderer;
    Game* gameManager;
    TTF_Font* font;

    double deltaTime;
};

