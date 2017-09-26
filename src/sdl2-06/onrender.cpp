#include"game.h"
void game::OnRender()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, &rectBackground, &displayRect);
    //display ground
    int s = position - 128;
    int e = position + (1440 * 900) / screenHeight;

    for (int c = s; c < e; c++) {
        if (c % groundRect.w == 0) {
            groundRect.x = c - position;
            SDL_RenderCopy(renderer, ground, NULL, &groundRect);
        }
    }

    //display building 1
    for (int c = s; c < e; c++) {
        if (c % (building1Rect.w * 5) == 0) {
            building1Rect.x = c - position;
            SDL_RenderCopy(renderer, building1, NULL, &building1Rect);
        }
    }

    //display building 2
    for (int c = s; c < e; c++) {
        if (c % (building2Rect.w * 7) == 0) {
            building2Rect.x = c - position;
            SDL_RenderCopy(renderer, building2, NULL, &building2Rect);
        }
    }

    //display building 3
    for (int c = s; c < e; c++) {
        if (c % (building3Rect.w * 11) == 0) {
            building3Rect.x = c - position;
            SDL_RenderCopy(renderer, building3, NULL, &building3Rect);
        }
    }

    SDL_RenderCopy(renderer, car, NULL, &carRect);
    SDL_RenderPresent(renderer);
}
