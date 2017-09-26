
#include <iostream>

#include "texture_manager.h"
#include "game.h"
#include "menu_button.h"
#include "play_state.h"
#include "main_menu_state.h"
#include "state_parser.h"
#include "input_handler.h"

const std::string MainMenuState::s_menuID = "MENU";
void MainMenuState::update()
{
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->update();
    }
}
void MainMenuState::render()
{
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->draw();
    }
}
bool MainMenuState::onEnter()
{
    StateParser stateparser;
    stateparser.parseState("Source/settings.json", s_menuID, &m_gameObjects, &m_textureIDList);
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_exitFromMenu);
    // set the callbacks for menu items
    setCallbacks(m_callbacks);
    std::cout << "entering MainMenuState\n";
    return true;
}

bool MainMenuState::onExit()
{
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->clean();
    }

    m_gameObjects.clear();

    for (size_t i = 0; i < m_textureIDList.size(); i++) {
        TextureManager::instance()->clearFromTextureMap(m_textureIDList[i]);
    }

    // 重置鼠标按键后上一步的点击效果不会影响到下一个状态
    InputHandler::instance()->reset();
    std::cout << "exiting MainMenuState" << std::endl;
    return true;
}

void MainMenuState::s_menuToPlay()
{
    std::cout << "Play button clicked" << std::endl;
    Game::instance()->getStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
    std::cout << "Exit button clicked" << std::endl;
    Game::instance()->quit();
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
    // go through the game objects
    for (int i = 0; i < m_gameObjects.size(); i++) {
        // if they are of type MenuButton then assign a callback
        // based on the id passed in from the file
        if (dynamic_cast<MenuButton*>(m_gameObjects[i])) {
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}
