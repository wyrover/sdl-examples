// ------------------------------------------------------------
// The Breakout Tutorial
// (c) 2015 Rembound.com
// http://rembound.com/articles/the-breakout-tutorial
// ------------------------------------------------------------

#ifndef ENTITY_H_
#define ENTITY_H_

#include "SDL.h"
#include "SDL_image.h"

class Entity {
public:
    Entity(SDL_Renderer* renderer);
    virtual ~Entity();

    float x, y, width, height;

    virtual void Update(float delta);
    virtual void Render(float delta);

    bool Collides(Entity* other);
protected:
    SDL_Renderer* renderer;

};

#endif
