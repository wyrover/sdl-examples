#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include"includes.h"

#define WIDTH 800
#define HEIGHT 600
//#define IMG_PATH "Track01.png"
class game
{
private:
    bool Running;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event Event;
    int screenWidth, screenHeight;
    SDL_Rect displayRect;

    SDL_Texture *car;
    SDL_Rect    carRect;

    SDL_Texture *background;
    SDL_Rect    rectBackground;

    SDL_Texture *building1;
    SDL_Rect    building1Rect;

    SDL_Texture *building2;
    SDL_Rect    building2Rect;

    SDL_Texture *building3;
    SDL_Rect    building3Rect;

    SDL_Texture *ground;
    SDL_Rect    groundRect;

    bool scrollRight, scrollLeft;

    int position;
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
