#include <iostream>
#include <SDL.h>
#include <tchar.h>
/*
 * Lesson 0: Test to make sure SDL is setup properly
 */
int _tmain(int argc, _TCHAR* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Quit();
    return 0;
}

