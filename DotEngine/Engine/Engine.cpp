#include "../Engine/Engine.h"


Engine::Engine()
{
    m_renderer = new DotRenderer();
    if(m_renderer){
        m_renderer->Init();
        m_gameManager = new Game(m_renderer);       
    }
    m_font = TTF_OpenFont("fonts/arial.ttf", 24);
	if (m_font == nullptr)
	{
		const char* err = SDL_GetError();
		TTF_Quit();
		SDL_Quit();
		return;
	}
}

Engine::~Engine()
{
    if(m_gameManager){
        delete m_gameManager;
    }
    if(m_renderer){
        delete m_renderer;
    }
    TTF_CloseFont(m_font);

    TTF_Quit();
	SDL_Quit();
}

int Engine::Validate()
{
    if(!m_gameManager || !m_renderer){
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
	m_deltaTime = 0;
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
		m_deltaTime = (double)(currentTick - lastTick) / SDL_GetPerformanceFrequency();
		lastTick = currentTick;

		frameCount++;
		fpsAccumulator += m_deltaTime;

		if (fpsAccumulator >= FPS_UPDATE_INTERVAL)
		{
			fps = frameCount / fpsAccumulator;
			frameCount = 0;
			fpsAccumulator = 0.0;
		}
        
        
        std::future<void> physicsTick = std::async(&Engine::PhysicsTick, this);
        
        RenderTick();
        
        physicsTick.get();
        
        FpsCounter(fps);
        
		m_renderer->Present();
        
        m_gameManager->CleanUp();
	}
}

void Engine::PhysicsTick()
{
    auto beforeTime = std::chrono::high_resolution_clock::now();
    while (true)
    {
        if(0 == m_gameManager->Update(m_deltaTime)) break;
    }
    auto afterTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> physicsTime = afterTime - beforeTime;
    DebugText("physics time ms: ", 60, physicsTime.count());
}
void Engine::RenderTick()
{ 
    auto renderTimeBefore = std::chrono::high_resolution_clock::now();

    m_renderer->Clear();
    m_gameManager->Render(m_deltaTime);
    m_renderer->RenderDots();

    auto renderTimeAfter = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> renderTime = renderTimeAfter - renderTimeBefore ;
    DebugText("render time ms: ", 30, (renderTime.count()));
}

void Engine::FpsCounter(double fps)
{
    // - FPS COUNTER -
    std::string fpsText = "FPS: " + std::to_string(static_cast<int>(fps));
    SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, fpsText.c_str(), 0, { 255, 255, 255, 255 }); 
    if (textSurface != nullptr)
    {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_renderer->GetSDLRenderer(), textSurface);
        if (textTexture != nullptr)
        {
            SDL_FRect renderQuad = { 0, 0, (float)textSurface->w, (float)textSurface->h }; 
            m_renderer->RenderTexture(textTexture, nullptr, &renderQuad);
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
    SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, fpsText.c_str(), 0, { 255, 255, 255, 255 }); 
    if (textSurface != nullptr)
    {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_renderer->GetSDLRenderer(), textSurface);
        if (textTexture != nullptr)
        {
            SDL_FRect renderQuad = { 0, offset, (float)textSurface->w, (float)textSurface->h }; 
            m_renderer->RenderTexture(textTexture, nullptr, &renderQuad);
            SDL_DestroyTexture(textTexture);
        }
        SDL_DestroySurface(textSurface);
    }
    // - FPS COUNTER -
}