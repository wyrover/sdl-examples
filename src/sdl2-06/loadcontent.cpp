#include"game.h"

bool game::LoadContent()
{
    int w = 0, h = 0;
    background = IMG_LoadTexture(renderer, "res/sdl2-06/background.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rectBackground.x = 0;
    rectBackground.y = 0;
    rectBackground.w = 256;
    rectBackground.h = h;
    car = IMG_LoadTexture(renderer, "res/sdl2-06/SideCar.png");
    SDL_QueryTexture(car, NULL, NULL, &w, &h);
    carRect.w = w * screenHeight / 900;
    carRect.h = h * screenHeight / 900;
    carRect.x = 0;
    carRect.y = 0.7 * screenHeight;
    building1 = IMG_LoadTexture(renderer, "res/sdl2-06/building1.png");
    SDL_QueryTexture(building1, NULL, NULL, &w, &h);
    building1Rect.w = w * screenHeight / 900;
    building1Rect.h = h * screenHeight / 900;
    building1Rect.x = 0;
    building1Rect.y = 0.72 * screenHeight - building1Rect.h;
    building2 = IMG_LoadTexture(renderer, "res/sdl2-06/building2.png");
    SDL_QueryTexture(building2, NULL, NULL, &w, &h);
    building2Rect.w = w * screenHeight / 900;
    building2Rect.h = h * screenHeight / 900;
    building2Rect.x = 0;
    building2Rect.y = 0.72 * screenHeight - building2Rect.h;
    building3 = IMG_LoadTexture(renderer, "res/sdl2-06/building3.png");
    SDL_QueryTexture(building3, NULL, NULL, &w, &h);
    building3Rect.w = w * screenHeight / 900;
    building3Rect.h = h * screenHeight / 900;
    building3Rect.x = 0;
    building3Rect.y = 0.72 * screenHeight - building3Rect.h;
    ground = IMG_LoadTexture(renderer, "res/sdl2-06/ground.png");
    SDL_QueryTexture(ground, NULL, NULL, &w, &h);
    groundRect.w = w * screenHeight / 900;
    groundRect.h = h * screenHeight / 900;
    groundRect.x = 0;
    groundRect.y = 0.72 * screenHeight;
    return 1;
}
