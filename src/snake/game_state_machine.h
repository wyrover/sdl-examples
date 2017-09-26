#ifndef __GAME_STATE_MACHINE_H__
#define __GAME_STATE_MACHINE_H__

#include "game_state.h"
#include <vector>
class GameStateMachine
{
public:
    void pushState(GameState* pState);
    void changeState(GameState* pState);
    void popState();
    void update();
    void render();

private:
    std::vector<GameState*> m_gameStates;
};
#endif
