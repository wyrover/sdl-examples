// ------------------------------------------------------------
// Porting Pong From Flash To C++
// http://rembound.com/articles/porting-pong-from-flash-to-cpp
// (c) 2014 Rembound.com
// ------------------------------------------------------------

#include "Paddle.h"

Paddle::Paddle(SDL_Renderer* renderer): Entity(renderer)
{
    // Load texture
    SDL_Surface* surface = IMG_Load("pong/assets/paddle.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    width = 32;
    height = 128;
    x = 0;
    y = 0;
}

Paddle::~Paddle()
{
    // Clean resources
    SDL_DestroyTexture(texture);
}

void Paddle::Update(float delta)
{
}

void Paddle::Render(float delta)
{
    SDL_Rect rect;
    rect.x = (int)(x + 0.5f); // Round the float to the nearest integer
    rect.y = (int)(y + 0.5f); // Round the float to the nearest integer
    rect.w = width;
    rect.h = height;
    SDL_RenderCopy(renderer, texture, 0, &rect);
}
