// #pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include "Game/Game.h"
#include "Engine/DotRenderer.h"
#include "Engine/Engine.h"


int main(int argc, char* args[])
{
// #ifdef _DEBUG
// 	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
// #endif

	Engine gameEngine = Engine();
	gameEngine.StartGame();

	return 0;
}