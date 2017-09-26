/****************
 * GG动画效果
 ***************/

#ifndef __ANIMATED_GRAPHIC_H__
#define __ANIMATED_GRAPHIC_H__

#include "sdl_game_object.h"
#include "game_object_factory.h"

class AnimatedGraphic : public SDLGameObject
{
public:

    void load(const LoaderParams* pParams);
    void draw();
    void update();
    void clean();

    AnimatedGraphic();

private:
    int m_animSpeed;
    int m_callbackID;
};

class AnimatedGraphicCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new AnimatedGraphic();
    }
};

#endif
