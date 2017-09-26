#ifndef __SNAKE_H__
#define  __SNAKE_H__

#include "game_object_factory.h"
#include "block.h"

#include <vector>

class Snake
{
public:
    void load(Block* block);
    void draw();
    void update();
    void clean();

    Snake();
    void eat();
    SDLGameObject* front();
    void grow(GameObject*);
    bool notBelong(int x, int y);
    bool eatSelf();
    bool hitWall();

private:
    void handleInput();
    void resetVelocity();
    int lastMove = SDL_GetTicks();
    int delay = 100;

    std::vector<Block*> m_snake;
    Vector2D m_velocity;

    bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
};


#endif
