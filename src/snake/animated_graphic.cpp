#include "animated_graphic.h"
#include "game.h"
#include "input_handler.h"
#include <iostream>

AnimatedGraphic::AnimatedGraphic() : SDLGameObject() {}

void AnimatedGraphic::load(const LoaderParams* pParams)
{
    SDLGameObject::load(pParams);
    m_animSpeed = pParams->getAnimSpeed();
    m_callbackID = pParams->getCallbackID();
    m_currentFrame = 0;
}

void AnimatedGraphic::draw()
{
    SDLGameObject::draw();
}

void AnimatedGraphic::update()
{
    m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % 3));
    SDLGameObject::update();
}

void AnimatedGraphic::clean() {}
