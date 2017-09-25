#include "trail.h"
#include "SDL_circle.h"

Trail::Trail(SDL_Renderer *r, unsigned int sizeX, unsigned int sizeY) : sizeX(sizeX), sizeY(sizeY)
{
    texture = SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, sizeX, sizeY);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(r, texture);
    SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
    SDL_RenderClear(r);
    SDL_SetRenderTarget(r, NULL);
}

void Trail::addCell(SDL_Renderer *r, Cell *c)
{
    auto t = SDL_GetRenderTarget(r);
    SDL_SetRenderTarget(r, texture);
    SDL_SetRenderDrawColor(r, 240, 240, 240, 100);
    SDL_RenderFillCircle(r,  c->getX(), c->getY(), c->getSize() / 2);
    SDL_SetRenderTarget(r, t);
}

void Trail::render(SDL_Renderer *renderer, SDL_Rect *section) const
{
    SDL_RenderCopy(renderer, texture, section, NULL);
}