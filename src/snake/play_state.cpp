#include "play_state.h"
#include "texture_manager.h"
#include "game.h"
#include "input_handler.h"
#include "pause_state.h"
#include "block.h"
#include "game_over_state.h"
#include "state_parser.h"

#include <iostream>
#include <cstdlib>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
    if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
        Game::instance()->getStateMachine()->pushState(new PauseState());
    }

    for (auto i : m_gameObjects) {
        i->update();
    }

    m_snake.update();

    if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects.back()),
                       dynamic_cast<SDLGameObject*>(m_snake.front()))) {
        m_snake.grow(m_gameObjects.back());
        m_gameObjects.clear();
        int x, y, width, height, numFrames, callbackID, animSpeed;
        std::string textureID;

        do {
            x = (rand() % (Game::s_screenWidth / 20)) * 20;
            y = (rand() % (Game::s_screenHeight / 20)) * 20;
        } while (!m_snake.notBelong(x, y));

        width = 20;
        height = 20;
        numFrames = 12;
        callbackID = 0;
        animSpeed = 0;
        textureID = "all_colors";
        GameObject* pGameObject = GameObjectFactory::instance()->create("Block");
        pGameObject->load(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed));
        m_gameObjects.push_back(pGameObject);
    }

    if (m_snake.eatSelf() || m_snake.hitWall()) {
        Game::instance()->getStateMachine()->pushState(new GameOverState());
    }
}

void PlayState::render()
{
    for (auto i : m_gameObjects) {
        i->draw();
    }

    m_snake.draw();
}

bool PlayState::onEnter()
{
    // parse the state
    StateParser stateParser;
    stateParser.parseState("Source/settings.json", s_playID, &m_gameObjects, &m_textureIDList);
    m_snake.grow(m_gameObjects.front());
    m_gameObjects.clear();
    int x, y, width, height, numFrames, callbackID, animSpeed;
    std::string textureID;

    do {
        x = (rand() % (Game::s_screenWidth / 20)) * 20;
        y = (rand() % (Game::s_screenHeight / 20)) * 20;
    } while (!m_snake.notBelong(x, y));

    width = 20;
    height = 20;
    numFrames = 12;
    callbackID = 0;
    animSpeed = 0;
    textureID = "all_colors";
    GameObject* pGameObject = GameObjectFactory::instance()->create("Block");
    pGameObject->load(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed));
    m_gameObjects.push_back(pGameObject);
    std::cout << "entering PlayState\n";
    return true;
}

bool PlayState::onExit()
{
    for (auto i : m_gameObjects) {
        i->clean();
    }

    m_gameObjects.clear();
    TextureManager::instance()->clearFromTextureMap("all_colors");
    std::cout << "exiting PlayState\n";
    return true;
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    leftA = p1->getPosition().getX();
    rightA = p1->getPosition().getX() + p1->getWidth();
    topA = p1->getPosition().getY();
    bottomA = p1->getPosition().getY() + p1->getHeight();
    //Calculate the sides of rect B
    leftB = p2->getPosition().getX();
    rightB = p2->getPosition().getX() + p2->getWidth();
    topB = p2->getPosition().getY();
    bottomB = p2->getPosition().getY() + p2->getHeight();

    //If any of the sides from A are outside of B
    if (bottomA <= topB) {
        return false;
    }

    if (topA >= bottomB) {
        return false;
    }

    if (rightA <= leftB) {
        return false;
    }

    if (leftA >= rightB) {
        return false;
    }

    std::cout << "collision!" << std::endl;
    return true;
}
