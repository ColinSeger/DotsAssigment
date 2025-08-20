#include "../Engine/DotRenderer.h"

DotRenderer::DotRenderer() 
{
	m_sdlRenderer = nullptr;
}

DotRenderer::DotRenderer(SDL_Window* window) : m_sdlRenderer(nullptr)
{
	m_sdlRenderer = SDL_CreateRenderer(window, nullptr);
	if (!m_sdlRenderer) return;
}

DotRenderer::~DotRenderer()
{
	if (m_sdlRenderer)
	{
		SDL_DestroyRenderer(m_sdlRenderer);
		m_sdlRenderer = nullptr;
	}
	if(m_gameWindow){
		SDL_DestroyWindow(m_gameWindow);
		m_gameWindow = nullptr;		
	}
}
int DotRenderer::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return 1;
	}
	if (!TTF_Init())
	{
		SDL_Quit();
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("Game", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

	m_sdlRenderer = SDL_CreateRenderer(window, nullptr);

	if (!m_sdlRenderer)
	{
		SDL_DestroyWindow(m_gameWindow);
		TTF_Quit();
		SDL_Quit();
		delete this;
		return 1;
	}

	// SetDrawColor(0x00, 0x00, 0x00, 0xFF);

	m_pixelBuffer.resize(SCREEN_WIDTH * SCREEN_HEIGHT, 0);
	m_bufferTexture = SDL_CreateTexture
	(
		m_sdlRenderer, 
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH,
		SCREEN_HEIGHT
	);
}
void DotRenderer::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(m_sdlRenderer, r, g, b, a);
}

void DotRenderer::Clear()
{
	std::fill(m_pixelBuffer.begin(), m_pixelBuffer.end(), 0);
	SDL_RenderClear(m_sdlRenderer);
}

void DotRenderer::Present()
{
	SDL_RenderPresent(m_sdlRenderer);
}
void DotRenderer::RenderDots()
{
	SDL_UpdateTexture(m_bufferTexture, NULL, m_pixelBuffer.data(), SCREEN_WIDTH * sizeof(uint32_t));
	RenderTexture(m_bufferTexture, NULL, NULL);
}

void DotRenderer::DrawPoint(int x, int y)
{
	SDL_RenderPoint(m_sdlRenderer, x, y);
}

void DotRenderer::DrawCircle(int centerX, int centerY, int radius)
{
	assert(m_sdlRenderer);

	int x = radius;
	int y = 0;
	int err = 0;

	while (x >= y) 
	{
		DrawPoint(centerX + x, centerY + y);
		DrawPoint(centerX + y, centerY + x);
		DrawPoint(centerX - y, centerY + x);
		DrawPoint(centerX - x, centerY + y);
		DrawPoint(centerX - x, centerY - y);
		DrawPoint(centerX - y, centerY - x);
		DrawPoint(centerX + y, centerY - x);
		DrawPoint(centerX + x, centerY - y);

		if (err <= 0) 
		{
			y++;
			err += 2 * y + 1;
		}
		if (err > 0) 
		{
			x--;
			err -= 2 * x + 1;
		}
	}
}

void DotRenderer::DrawFilledCircle(int centerX, int centerY, int radius, uint32_t color)
{
	int minX = std::max(0, centerX - radius);
	int maxX = std::min(SCREEN_WIDTH -1, centerX + radius);
	int minY = std::max(0, centerY - radius);
	int maxY = std::min(SCREEN_HEIGHT -1, centerY + radius);

	for(int y = minY; y <= maxY; y++){
		for(int x = minX; x <= maxX; x++){
			int dx = x - centerX;
			int dy = y - centerY;

			if(dx * dx + dy * dy <= radius * radius){
				int index = y * SCREEN_WIDTH + x;

				m_pixelBuffer[index] = color;
			}
		}
	}
}

void DotRenderer::RenderTexture(SDL_Texture* texture, const SDL_FRect* srcRect, const SDL_FRect* dstRect)
{
	SDL_RenderTexture(m_sdlRenderer, texture, srcRect, dstRect);
}




