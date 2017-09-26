#include "lib/Tetris.h"
#include <tchar.h>

#ifdef WIN32
int _tmain(int argc, _TCHAR* argv[])
#else
extern "C" int SDL_main(int argc, char *argv[])
#endif
{
    Tetris::Tetris tetris;

    tetris.start();

    return 0;
}
