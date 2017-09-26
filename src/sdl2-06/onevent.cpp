#include"game.h"

void game::OnEvent(SDL_Event* Event)
{
    //handle window close
    if (Event->type == SDL_QUIT) {
        Running = false;
    }

    //handle screen resize
    if (Event->type == SDL_WINDOWEVENT) {
        int w = 0, h = 0;

        switch (Event->window.event) {
        case SDL_WINDOWEVENT_RESIZED:
            SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);
            displayRect.w = screenWidth;
            displayRect.h = screenHeight;
            displayRect.x = displayRect.y = 0;
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
            break;
        }
    }

    //handle key press
    if (Event->type == SDL_KEYDOWN) {
        switch (Event->key.keysym.sym) {
        case SDLK_d:
            scrollRight = 1;
            break;

        case SDLK_a:
            scrollLeft = 1;
            break;

        case SDLK_ESCAPE:
            Running = false;
            break;
        }
    }

    //handle key release
    if (Event->type == SDL_KEYUP) {
        switch (Event->key.keysym.sym) {
        case SDLK_d:
            scrollRight = 0;
            break;

        case SDLK_a:
            scrollLeft = 0;
            break;
        }
    }
}
