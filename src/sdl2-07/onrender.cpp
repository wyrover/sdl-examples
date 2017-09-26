#include"game.h"
void game::OnRender()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, Map, NULL, &rectMap);
    SDL_RenderPresent(renderer);
}
