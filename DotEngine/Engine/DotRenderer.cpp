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
	if(gameWindow){
		SDL_DestroyWindow(gameWindow);
		gameWindow = nullptr;		
	}
}
int DotRenderer::Init(int width, int height)
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

	SDL_Window* window = SDL_CreateWindow("Game", width, height, SDL_WINDOW_OPENGL);

	m_sdlRenderer = SDL_CreateRenderer(window, nullptr);

	if (!m_sdlRenderer)
	{
		SDL_DestroyWindow(gameWindow);
		TTF_Quit();
		SDL_Quit();
		delete this;
		return 1;
	}

	SetDrawColor(0x00, 0x00, 0x00, 0xFF);
}
void DotRenderer::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	if (m_sdlRenderer)
	{
		SDL_SetRenderDrawColor(m_sdlRenderer, r, g, b, a);
	}
}

void DotRenderer::Clear()
{
	if (m_sdlRenderer)
	{
		SDL_RenderClear(m_sdlRenderer);
	}
}

void DotRenderer::Present()
{
	if (m_sdlRenderer)
	{
		SDL_RenderPresent(m_sdlRenderer);
	}
}

void DotRenderer::DrawPoint(int x, int y)
{
	if (m_sdlRenderer)
	{
		SDL_RenderPoint(m_sdlRenderer, x, y);
	}
}

void DotRenderer::DrawCircle(int centerX, int centerY, int radius)
{
	if (!m_sdlRenderer) return;

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

void DotRenderer::DrawFilledCircle(int centerX, int centerY, int radius)
{
	if (!m_sdlRenderer) return;

	for (int y = -radius; y <= radius; y++) 
	{
		int x = static_cast<int>(std::sqrt(radius * radius - y * y));
		SDL_RenderLine(m_sdlRenderer, centerX - x, centerY + y, centerX + x, centerY + y);
	}
}

void DotRenderer::RenderTexture(SDL_Texture* texture, const SDL_FRect* srcRect, const SDL_FRect* dstRect)
{
	if (m_sdlRenderer && texture)
	{
		SDL_RenderTexture(m_sdlRenderer, texture, srcRect, dstRect);
	}
}




