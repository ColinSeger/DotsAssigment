#pragma once
#include "../Engine/DotRenderer.h"
#include "../Engine/Constants.h"
#include "../Game/Game.h"
#include <chrono>
#include <future>

class Engine
{
public:
    Engine();
    ~Engine();

    int Validate();

    int StartGame();

    const Game* GetGameManager(){ return m_gameManager; }

    DotRenderer* GetRender(){ return m_renderer; }

private:

    void Tick();
    void PhysicsTick();
    void FpsCounter(double fps);
    void DebugText(std::string text, int offset, double fps);

    DotRenderer* m_renderer = nullptr;
    Game* m_gameManager = nullptr;
    TTF_Font* m_font = nullptr;

    double m_deltaTime = 0;
};

