#ifndef __SDL_GAME_OBJECT_H__
#define __SDL_GAME_OBJECT_H__

#include "game_object.h"
#include "vector2d.h"

class SDLGameObject : public GameObject
{
public:
    SDLGameObject();
    virtual void draw();
    virtual void update();
    virtual void clean();
    Vector2D& getPosition()
    {
        return m_position;
    }
    void setPosition(Vector2D newP);
    int getWidth()
    {
        return m_width;
    }
    int getHeight()
    {
        return m_height;
    }
    void load(const LoaderParams *pParams);

protected:
    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;

    int m_currentRow;
    int m_currentFrame;
    int m_numFrames;
    std::string m_textureID;

};
#endif
