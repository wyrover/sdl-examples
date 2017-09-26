#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
    Release();
}

void Renderer::Release()
{
    SDL_DestroyRenderer(m_pRenderer);
    m_pRenderer = nullptr;
}

void Renderer::ClearBackBuffer()
{
    SDL_SetRenderDrawColor(m_pRenderer, m_BackgroundColor.r, m_BackgroundColor.g, m_BackgroundColor.b, m_BackgroundColor.a);
    SDL_RenderClear(m_pRenderer);
}

void Renderer::Present()
{
    if (m_pRenderer) {
        //Update screen
        SDL_RenderPresent(m_pRenderer);
        //Clear screen ready for next frame
        ClearBackBuffer();
    }
}

bool Renderer::Create(SDL_Window* pWindow, Uint32 flags /*= SDL_RENDERER_ACCELERATED*/, int index /*= -1*/)
{
    if (!pWindow)
        return false;

    Release();
    m_pRenderer = SDL_CreateRenderer(pWindow, index, flags);

    if (m_pRenderer == nullptr)
        return false;

    ClearBackBuffer();
    return true;
}