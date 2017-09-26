// ------------------------------------------------------------
// Porting Pong From Flash To C++
// http://rembound.com/articles/porting-pong-from-flash-to-cpp
// (c) 2014 Rembound.com
// ------------------------------------------------------------

#ifndef ENTITY_H_
#define ENTITY_H_

#include "SDL.h"
#include "SDL_image.h"

class Entity
{
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
