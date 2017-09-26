#ifndef _RENDERER_H_
#define _RENDERER_H_

#pragma once

#include <SDL.h>

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void Release();

    void ClearBackBuffer();

    void Present();

    bool Create(SDL_Window* pWindow, Uint32 flags = SDL_RENDERER_ACCELERATED, int index = -1);

    SDL_Renderer* GetRenderPtr()
    {
        return m_pRenderer;
    }

private:
    SDL_Renderer* m_pRenderer = nullptr;
    SDL_Color m_BackgroundColor = SDL_Color{ 0x00, 0x00, 0x00, 0xFF };
};

#endif _RENDERER_H_