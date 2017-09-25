#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include "MenuState.h"
#include "GameObject.h"
#include <vector>

class GameOverState : public MenuState
{
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_gameOverID; }

private:
    static const std::string s_gameOverID;
    std::vector<GameObject*> m_gameObjects;

    //call back functions for menu items
    static void s_gameOverToMain();
    static void s_restartPlay();
    virtual void setCallbacks(const std::vector<Callback>& callbacks);
};

#endif