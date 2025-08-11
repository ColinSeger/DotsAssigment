#pragma once
#include "glm/glm.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cmath> 
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

class DotRenderer
{
public:

    DotRenderer();
    DotRenderer(SDL_Window* window);
    

    ~DotRenderer();
    
    
    int Init(int width, int height);


    SDL_Renderer* GetSDLRenderer() const { return m_sdlRenderer; }

    void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void Clear();
    void Present();

    void DrawCircle(int centerX, int centerY, int radius);
    void DrawFilledCircle(int centerX, int centerY, int radius);
    void RenderTexture(SDL_Texture* texture, const SDL_FRect* srcRect, const SDL_FRect* dstRect);

    void DrawLineBetweenPoints(glm::vec2 point1, glm::vec2 point2){
        SetDrawColor(0,255,0,255);
		SDL_RenderLine(m_sdlRenderer, point1.x, point1.y, point2.x, point2.y);
	}
    DotRenderer operator=(const DotRenderer& newRender){
        this->gameWindow = newRender.gameWindow;
        this->m_sdlRenderer = newRender.m_sdlRenderer;
    }
private:
    SDL_Window* gameWindow;
    SDL_Renderer* m_sdlRenderer;

    void DrawPoint(int x, int y);

    DotRenderer(const DotRenderer&) = delete;
    // DotRenderer& operator=(const DotRenderer&) = delete;
};

