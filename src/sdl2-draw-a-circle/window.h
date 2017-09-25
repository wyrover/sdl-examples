/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

class Window
{
public:
    Window();
    ~Window();
private:
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
};
