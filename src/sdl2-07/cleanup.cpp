#include"game.h"

void game::Cleanup()
{
    SDL_DestroyTexture(Map);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}