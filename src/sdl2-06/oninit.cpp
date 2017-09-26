#include"game.h"

bool game::OnInit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    //Creates a SDL Window
    if ((window = SDL_CreateWindow("Image Loading", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE)) == NULL) {
        return false;
    }

    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }

    //adjust displayRect to size of screen
    SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);
    displayRect.w = screenWidth;
    displayRect.h = screenHeight;
    displayRect.x = displayRect.y = 0;
    int w = 0, h = 0;
    SDL_QueryTexture(car, NULL, NULL, &w, &h);
    carRect.w = w * screenHeight / 900;
    carRect.h = h * screenHeight / 900;
    carRect.x = 0;
    carRect.y = 0.7 * screenHeight;
    SDL_QueryTexture(ground, NULL, NULL, &w, &h);
    groundRect.w = w * screenHeight / 900;
    groundRect.h = h * screenHeight / 900;
    groundRect.x = 0;
    groundRect.y = 0.72 * screenHeight;
    SDL_QueryTexture(building1, NULL, NULL, &w, &h);
    building1Rect.w = w * screenHeight / 900;
    building1Rect.h = h * screenHeight / 900;
    building1Rect.x = 0;
    building1Rect.y = 0.72 * screenHeight - building1Rect.h;
    SDL_QueryTexture(building2, NULL, NULL, &w, &h);
    building2Rect.w = w * screenHeight / 900;
    building2Rect.h = h * screenHeight / 900;
    building2Rect.x = 0;
    building2Rect.y = 0.72 * screenHeight - building2Rect.h;
    SDL_QueryTexture(building3, NULL, NULL, &w, &h);
    building3Rect.w = w * screenHeight / 900;
    building3Rect.h = h * screenHeight / 900;
    building3Rect.x = 0;
    building3Rect.y = 0.72 * screenHeight - building3Rect.h;
    scrollRight = 0;
    scrollLeft = 0;
    return true;
}
