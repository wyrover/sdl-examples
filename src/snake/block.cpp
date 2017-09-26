#include "block.h"
#include "game.h"
#include "input_handler.h"
#include <iostream>

Block::Block() : SDLGameObject() {}

void Block::load(const LoaderParams* pParams)
{
    SDLGameObject::load(pParams);
}

void Block::draw()
{
    SDLGameObject::draw();
}

void Block::update()
{
    m_currentFrame = int(((SDL_GetTicks() / 100) % 12));
    SDLGameObject::update();
}

void Block::clean() {}
