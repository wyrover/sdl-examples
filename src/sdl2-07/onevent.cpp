#include"game.h"

void game::OnEvent(SDL_Event* Event)
{
    if (Event->type == SDL_QUIT) {
        Running = false;
    }

    if (Event->type == SDL_WINDOWEVENT) {
        switch (Event->window.event) {
        case SDL_WINDOWEVENT_RESIZED:
            SDL_GetRendererOutputSize(renderer, &rectMap.w, &rectMap.h);
            break;
        }
    }
}
