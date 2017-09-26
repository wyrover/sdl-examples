#include "header.h"
#include "Core.h"
#include <tchar.h>

#ifdef WIN32
    int _tmain(int argc, _TCHAR* argv[])
#else
    extern "C" int SDL_main(int argc, char *argv[])
#endif
{
    CCore oCore;
    oCore.mainLoop();
    return 0;
}
