
#include <iostream>

#include "game.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* argv[])
{
    Uint32 frameStart, frameTime;
    std::cout << "game init attempt...\n";

    if (Game::instance()->init("Chapter 1", 100, 100, 640, 480, false)) {
        while (Game::instance()->running()) {
            frameStart = SDL_GetTicks();
            Game::instance()->handleEvents();
            Game::instance()->update();
            Game::instance()->render();
            frameTime = SDL_GetTicks() - frameStart;

            if (frameTime < DELAY_TIME) {
                SDL_Delay((int)(DELAY_TIME - frameTime));
            }
        }
    } else {
        std::cout << "game init failure - " << SDL_GetError() << "\n";
        return -1;
    }

    std::cout << "game closing...\n";
    Game::instance()->clean();
    return 0;
}
