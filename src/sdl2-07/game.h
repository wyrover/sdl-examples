#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include"includes.h"

#define WIDTH 800
#define HEIGHT 600
class game
{
private:
    bool Running;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event Event;

    SDL_Texture *Map;
    SDL_Rect rectMap;
public:
    game();
    int OnExecute();
    bool OnInit();
    bool LoadContent();
    void OnEvent(SDL_Event* Event);
    void OnLoop();
    void OnRender();
    void Cleanup();

};
#endif // GAME_H_INCLUDED
