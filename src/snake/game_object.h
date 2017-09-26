// 表示游戏中的所有实体

#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <SDL.h>
#include <string>

#include "loader_params.h"

class GameObject
{
public:
    // virtual void load(int x, int y, int width, int height, std::string textureID) = 0;
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;

    virtual void load(const LoaderParams* pParams) = 0;

protected:
    // 暂时用不上
    int m_x;
    int m_y;

    int m_width;
    int m_height;
    int m_currentRow;
    int m_currentFrame;
    std::string m_textureID;
    GameObject() {}
    virtual ~GameObject() {}
};

#endif
