#pragma once
#include "../Engine/DotRenderer.h"
#include "../Game/Game.h"

// static const int SCREEN_WIDTH = 1000;
// static const int SCREEN_HEIGHT = 800;
// static const glm::vec2 SCREEN_CENTRE = {SCREEN_WIDTH /2, SCREEN_HEIGHT / 2};

class Engine
{
public:
    Engine();
    ~Engine();

    int Init();

    int StartGame();

    const Game* GetGameManager(){ return gameManager; }

    DotRenderer* GetRender(){ return renderer; }
private:
    DotRenderer* renderer;
    Game* gameManager;
};

