#include <memory>
#include <tchar.h>

#include "GameApp.h"
#include "StartMenuState.h"
#include "PongState.h"

#ifdef WIN32
    int _tmain(int argc, _TCHAR* argv[])
#else
    extern "C" int SDL_main(int argc, char *argv[])
#endif
{
    WindowCreationParams createParam;
    GameApp app("Moving Ball");
    app.Register<StartMenuState>("MENUSTATE");
    app.Register<PongState>("PONGSTATE");
    return app.Execute(createParam, "MENUSTATE");
}
