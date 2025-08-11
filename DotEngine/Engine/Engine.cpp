#include "../Engine/Engine.h"


Engine::Engine()
{
    renderer = new DotRenderer();
    if(renderer){
        renderer->Init(SCREEN_WIDTH, SCREEN_HEIGHT);
        gameManager = new Game(renderer);       
    }
}

Engine::~Engine()
{
    if(renderer){
        delete renderer;
    }
}

int Engine::Init()
{
    return 0;
}

int Engine::StartGame()
{
    return 0;
}