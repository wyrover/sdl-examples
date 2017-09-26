#include"game.h"

void game::Cleanup()
{
    SDL_DestroyTexture(car);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(building1);
    SDL_DestroyTexture(building2);
    SDL_DestroyTexture(building3);
    SDL_DestroyTexture(ground);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
