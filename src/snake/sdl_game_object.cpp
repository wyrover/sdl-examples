#include "sdl_game_object.h"
#include "texture_manager.h"
#include "game.h"

SDLGameObject::SDLGameObject() : GameObject(), m_position(0, 0), m_velocity(0, 0),
    m_acceleration(0, 0)
{
}

void SDLGameObject::draw()
{
    if (m_velocity.getX() > 0) {
        TextureManager::instance()->drawFrame(m_textureID, (int)m_position.getX(),
                                              (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame,
                                              Game::instance()->getRenderer(), SDL_FLIP_HORIZONTAL);
    } else {
        TextureManager::instance()->drawFrame(m_textureID, (int)m_position.getX(),
                                              (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame,
                                              Game::instance()->getRenderer());
    }
}

void SDLGameObject::update()
{
    m_velocity += m_acceleration;
    m_position += m_velocity;
}

void SDLGameObject::clean() {}

void SDLGameObject::load(const LoaderParams *pParams)
{
    m_position = Vector2D(pParams->getX(), pParams->getY());
    m_velocity = Vector2D(0, 0);
    m_acceleration = Vector2D(0, 0);
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();
    m_currentRow = 1;
    m_currentFrame = 1;
    m_numFrames = pParams->getNumFrames();
}

void SDLGameObject::setPosition(Vector2D newP)
{
    m_position = newP;
}
