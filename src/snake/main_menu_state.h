#ifndef __MAIN_MENU_STATE_H__
#define __MAIN_MENU_STATE_H__

#include "menu_state.h"
#include "game_object.h"

#include <vector>

class MainMenuState : public MenuState
{
public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    virtual std::string getStateID() const
    {
        return s_menuID;
    }
private:
    static const std::string s_menuID;
    std::vector<GameObject*> m_gameObjects;

    static void s_menuToPlay();
    static void s_exitFromMenu();

    virtual void setCallbacks(const std::vector<Callback>& callbacks);
};
#endif
