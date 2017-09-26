#ifndef LINUX
    #include <windows.h>
    #include <stdlib.h>
    #include <tchar.h>
#endif
#include "Game.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

/*
=========================
main
==========================
*/
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    // Initializing game objects
    View view;
    Commands cmds;
    int screenHeight = view.getScreenHeight();
    Game game(&view, &cmds, screenHeight);
    bool quit = false;
    SDL_Event e;
    //Get the actual clock in milliseconds (SDL)
    unsigned long time1 = SDL_GetTicks();

    // ------Main Loop ---------------
    while (!quit) {
        game.drawScene();
        int key = cmds.pollkey(&e);

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                quit = true;
        }

        //-------input----------
        switch (key) {
        case (10): {
            quit = true;
        }

        case (SDLK_RIGHT): {
            if (game.board->isPossibleMovement(game.posX + 1, game.posY))
                game.posX++;

            break;
        }

        case (SDLK_LEFT): {
            if (game.board->isPossibleMovement(game.posX - 1, game.posY))
                game.posX--;

            break;
        }

        case (SDLK_DOWN): {
            if (game.board->isPossibleMovement(game.posX, game.posY + 1))
                game.posY++;

            break;
        }

        case (SDLK_SPACE): {
            // check collision from up to the possible bottom
            while (game.board->isPossibleMovement(game.posX, game.posY)) {
                game.posY++;
            }

            game.board->storePiece(game.posX, game.posY - 1);
            game.board->deletePossibleLines();

            if (game.board->isGameOver()) {
                if (!game.restart()) goto exit_loop;
            }

            game.createNewPiece();
            break;
        }

        case (SDLK_UP): {
            game.piece->rotatePiece();

            if (!game.board->isPossibleMovement(game.posX, game.posY)) {
                int i = 3;
                game.piece->rotatePiece(3);  //
            }

            break;
        }
        }

        // -------- vertical movement --------------
        unsigned long time2 = SDL_GetTicks();

        if ((time2 - time1) > WAIT_TIME) {
            if (game.board->isPossibleMovement(game.posX, game.posY + 1)) {
                game.posY++;
            } else {
                game.board->storePiece(game.posX, game.posY);
                game.board->deletePossibleLines();

                if (game.board->isGameOver()) {
                    if (!game.restart()) break;
                }

                game.createNewPiece();
            }

            time1 = SDL_GetTicks();
        }
    }

exit_loop:
    ;
    view.cleanUp();
    return 0;
}
