#include "game_over_state.h"
#include "game.h"
#include "main_menu_state.h"
#include "play_state.h"
#include "animated_graphic.h"
#include "menu_button.h"
#include "state_parser.h"
#include "input_handler.h"

#include <iostream>


const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::s_gameOverToMain()
{
    Game::instance()->getStateMachine()->changeState(new MainMenuState());
}

void GameOverState::s_restartPlay()
{
    Game::instance()->getStateMachine()->changeState(new PlayState());
}

bool GameOverState::onEnter()
{
    StateParser stateParser;
    stateParser.parseState("Source/settings.json", s_gameOverID, &m_gameObjects,
                           &m_textureIDList);
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_gameOverToMain);
    m_callbacks.push_back(s_restartPlay);
    setCallbacks(m_callbacks);
    std::cout << "entering GameOverState" << std::endl;
    return true;
}

void GameOverState::update()
{
    for (auto i : m_gameObjects) {
        i->update();
    }
}

void GameOverState::render()
{
    for (auto i : m_gameObjects) {
        i->draw();
    }
}

bool GameOverState::onExit()
{
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->clean();
    }

    m_gameObjects.clear();

    for (int i = 0; i < m_textureIDList.size(); i++) {
        TextureManager::instance()->clearFromTextureMap(m_textureIDList[i]);
    }

    InputHandler::instance()->reset();
    std::cout << "exiting GameOverState" << std::endl;
    return true;
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
{
    // go through the game objects
    for (int i = 1; i < m_gameObjects.size(); i++) {
        // if they are of type MenuButton then assign a callback based
        // on the id passed in from the file
        if (dynamic_cast<MenuButton*>(m_gameObjects[i])) {
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}
