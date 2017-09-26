#ifndef __PLAY_STATE_H__
#define __PLAY_STATE_H__

#include "game_state.h"
#include "game_object.h"
#include "sdl_game_object.h"
#include "snake.h"

#include <string>
#include <vector>
class PlayState : public GameState
{
public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    virtual std::string getStateID() const
    {
        return s_playID;
    }

    bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
private:
    static const std::string s_playID;
    std::vector<GameObject*> m_gameObjects;
    Snake m_snake;
};
#endif
