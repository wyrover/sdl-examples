// ------------------------------------------------------------
// The Breakout Tutorial
// (c) 2015 Rembound.com
// http://rembound.com/articles/the-breakout-tutorial
// ------------------------------------------------------------

#include "main.h"
#include <tchar.h>

#ifdef WIN32
    int _tmain(int argc, _TCHAR* argv[])
#else
    extern "C" int SDL_main(int argc, char *argv[])
#endif
{
    // Create the game object
    Game* game = new Game();

    // Initialize and run the game
    if (game->Init()) {
        game->Run();
    }

    // Clean up
    delete game;
    return 0;
}
