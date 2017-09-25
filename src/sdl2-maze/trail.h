#ifndef _MAZE_TRAIL_H_
#define _MAZE_TRAIL_H_
#include <SDL.h>
#include "cell.h"
#include <vector>
class Trail
{
protected:
    SDL_Texture *texture;
    std::vector<Cell *> cells;
    unsigned int sizeX;
    unsigned int sizeY;
public:
    Trail(SDL_Renderer *r, unsigned int sizeX, unsigned int sizeY);
    void addCell(SDL_Renderer *r, Cell *c);
    void render(SDL_Renderer *renderer, SDL_Rect *section) const;
};

#endif