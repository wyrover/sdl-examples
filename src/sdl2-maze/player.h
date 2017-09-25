#ifndef _MAZE_PLAYER_H_
#define _MAZE_PLAYER_H_

#include <SDL.h>
#include "cell.h"
#include "trail.h"

class Player
{
    SDL_Renderer *renderer;
    Trail *trail;
    Cell *currentCell;
    int keyDown;
    int keyTimeout;
public:
    Player(SDL_Renderer *r, Trail *trail, Cell *cell);
    void handleEvent(SDL_Event *e);

    void render(SDL_Rect *section) const;

    void moveToCell(Cell *moveCell);
    Cell *getCellForKey(int key) const;

    Cell *getCell() const
    {
        return currentCell;
    }
    void setCell(Cell *c)
    {
        currentCell = c;
    }
};

#endif