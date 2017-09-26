/**************************************************************************
 * Commands.cpp - Class that handles inputs (keyboard inputs)
 *
 * @author Abesari Woldeyesus (abesary@bu.edu)
 *
/**************************************************************************/

#include "Commands.h"

/*
======================================
Keyboard Input
======================================
*/
int Commands::pollkey(SDL_Event *event)
{
    //SDL_Event event;
    while (SDL_PollEvent(event)) {
        switch (event->type) {
        case SDL_KEYDOWN:
            return event->key.keysym.sym;

        case SDL_WINDOWEVENT_CLOSE:
            exit(3);

        case SDL_QUIT:
            return 10;
        }
    }

    return -1;
}


/*
======================================
Keyboard Input
======================================
*/
int Commands::isKeyDown(int pKey)
{
    const Uint8* myKeytable;
    int mNumkeys;
    SDL_PumpEvents();
    myKeytable = SDL_GetKeyboardState(&mNumkeys);
    return myKeytable[pKey];
}
