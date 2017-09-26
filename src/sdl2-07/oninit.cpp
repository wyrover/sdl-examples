#include"game.h"

bool game::OnInit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    //Creates a SDL Window
    if ((window = SDL_CreateWindow("Create and Save Image", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL) {
        return false;
    }

    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }

    return true;
}
