#include"game.h"
#include <tchar.h>

game::game()
{
    window = NULL;
    Running = true;
    Map = NULL;
}

int game::OnExecute()
{
    if (OnInit() == false) {
        return -1;
    }

    if (LoadContent() == false) {
        return -1;
    }

    while (Running) {
        while (SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }

    Cleanup();
    return 0;
}

#ifdef WIN32
    int _tmain(int argc, _TCHAR* argv[])
#else
    extern "C" int SDL_main(int argc, char *argv[])
#endif
{
    game theGame;
    return theGame.OnExecute();
}
