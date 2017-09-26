// ------------------------------------------------------------
// Porting Pong From Flash To C++
// http://rembound.com/articles/porting-pong-from-flash-to-cpp
// (c) 2014 Rembound.com
// ------------------------------------------------------------

#ifndef BOARD_H_
#define BOARD_H_

#include "Entity.h"
#include <stdlib.h>
#include <time.h>

class Board: public Entity
{
public:
    Board(SDL_Renderer* renderer);
    ~Board();

    void Update(float delta);
    void Render(float delta);

    float boundtop, boundbottom;

private:
    SDL_Texture* sidetexture;
};

#endif
