#include <windows.h>
#include <tchar.h>
#include <SDL.h>


int _tmain(int argc, _TCHAR* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Init(SDL_INIT_VIDEO);
    int horizontal;
    int vertical;
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    horizontal = desktop.right;
    vertical = desktop.bottom;
    window = SDL_CreateWindow("Death By Darkness", 0, 0, horizontal, vertical, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    //SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, 640, 480);
    // Clear the window and make it all green
    SDL_RenderClear(renderer);
    // Change color to blue
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    // Change color to green
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    // Render the changes above
    SDL_RenderPresent(renderer);
    SDL_Delay(3000);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}