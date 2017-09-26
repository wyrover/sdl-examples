// ------------------------------------------------------------
// The Breakout Tutorial
// (c) 2015 Rembound.com
// http://rembound.com/articles/the-breakout-tutorial
// ------------------------------------------------------------

#ifndef PADDLE_H_
#define PADDLE_H_

#include "Entity.h"

class Paddle: public Entity
{
public:
    Paddle(SDL_Renderer* renderer);
    ~Paddle();

    void Update(float delta);
    void Render(float delta);

private:
    SDL_Texture* texture;
};

#endif
