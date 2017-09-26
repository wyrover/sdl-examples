#ifndef __MENU_BUTTON_H__
#define __MENU_BUTTON_H__

#include "sdl_game_object.h"
#include "game_object_factory.h"

class MenuButton : public SDLGameObject
{
public:
    MenuButton();
    void draw();
    void update();
    void clean();
    void load(const LoaderParams* pParams);

    void setCallback(void(*callback)())
    {
        m_callback = callback;
    }
    int getCallbackID()
    {
        return m_callbackID;
    }

private:
    enum button_state {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };

    void (*m_callback)();
    bool m_bReleased;
    int m_callbackID;
};

class MenuButtonCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new MenuButton();
    }
};
#endif
