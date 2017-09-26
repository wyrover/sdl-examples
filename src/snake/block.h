#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "sdl_game_object.h"
#include "game_object_factory.h"

class Block : public SDLGameObject
{
public:

    void load(const LoaderParams* pParams);
    void draw();
    void update();
    void clean();

    Block();
};

class BlockCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Block();
    }
};

#endif
