#include "../Engine/Engine.h"


Engine::Engine()
{
    renderer = new DotRenderer();
    if(renderer){
        renderer->Init();
        gameManager = new Game(renderer);       
    }
    font = TTF_OpenFont("fonts/arial.ttf", 24);
	if (font == nullptr)
	{
		const char* err = SDL_GetError();
		TTF_Quit();
		SDL_Quit();
		return;
	}
}

Engine::~Engine()
{
    if(gameManager){
        delete gameManager;
    }
    if(renderer){
        delete renderer;
    }
    TTF_CloseFont(font);

    TTF_Quit();
	SDL_Quit();
}

int Engine::Validate()
{
    if(!gameManager || !renderer){
        return 1;
    }
    return 0;
}

int Engine::StartGame()
{
    Tick();
    return 0;
}

void Engine::Tick()
{
    bool quit = false;
	SDL_Event event;

	Uint64 lastTick = SDL_GetPerformanceCounter();
	Uint64 currentTick;
	deltaTime = 0;
	double fps = 0;
	int frameCount = 0;
	double fpsAccumulator = 0.0;
	const double FPS_UPDATE_INTERVAL = 0.2f;

    while (!quit)
	{
        while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_EVENT_QUIT)
			{
				quit = true;
			}
		}
		currentTick = SDL_GetPerformanceCounter();
		deltaTime = (double)(currentTick - lastTick) / SDL_GetPerformanceFrequency();
		lastTick = currentTick;

		frameCount++;
		fpsAccumulator += deltaTime;

		if (fpsAccumulator >= FPS_UPDATE_INTERVAL)
		{
			fps = frameCount / fpsAccumulator;
			frameCount = 0;
			fpsAccumulator = 0.0;
		}
        
        auto beforeTime = std::chrono::high_resolution_clock::now();
        std::future<void> tick = std::async(&Engine::PhysicsTick, this);
        // PhysicsTick();
        auto renderTimeBefore = std::chrono::high_resolution_clock::now();
        renderer->SetDrawColor(0x00, 0x00, 0x00, 0xFF); 
		renderer->Clear();
        
        gameManager->Render(deltaTime);
        renderer->RenderDots();
        auto renderTimeAfter = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> renderTime = renderTimeAfter - renderTimeBefore ;

        DebugText("render time ms: ", 30, renderTime.count());
        
        tick.get();
        FpsCounter(fps);
        auto afterTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> physicsTime = afterTime - beforeTime;
        double physTime = physicsTime.count() - renderTime.count();
        DebugText("physics time ms: ", 60, physTime);
		renderer->Present();
        
        gameManager->CleanUp();
	}
}

void Engine::PhysicsTick()
{
    while (true)
    {
        if(0 == gameManager->Update(deltaTime)) return;
    }
}

void Engine::FpsCounter(double fps)
{
    // - FPS COUNTER -
    std::string fpsText = "FPS: " + std::to_string(static_cast<int>(fps));
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, fpsText.c_str(), 0, { 255, 255, 255, 255 }); 
    if (textSurface != nullptr)
    {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer->GetSDLRenderer(), textSurface);
        if (textTexture != nullptr)
        {
            SDL_FRect renderQuad = { 0, 0, (float)textSurface->w, (float)textSurface->h }; 
            renderer->RenderTexture(textTexture, nullptr, &renderQuad);
            SDL_DestroyTexture(textTexture);
        }
        SDL_DestroySurface(textSurface);
    }
    // - FPS COUNTER -
}

void Engine::DebugText(std::string text, int offset, double value)
{
    // - FPS COUNTER -
    std::string fpsText = text + std::to_string(static_cast<int>(value));
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, fpsText.c_str(), 0, { 255, 255, 255, 255 }); 
    if (textSurface != nullptr)
    {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer->GetSDLRenderer(), textSurface);
        if (textTexture != nullptr)
        {
            SDL_FRect renderQuad = { 0, offset, (float)textSurface->w, (float)textSurface->h }; 
            renderer->RenderTexture(textTexture, nullptr, &renderQuad);
            SDL_DestroyTexture(textTexture);
        }
        SDL_DestroySurface(textSurface);
    }
    // - FPS COUNTER -
}