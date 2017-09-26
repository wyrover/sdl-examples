#include "snake.h"
#include "game.h"
#include "input_handler.h"

#include <iostream>

int INIT_VELOCITY = 20;

Snake::Snake(): m_velocity(0, 0) {}

void Snake::load(Block* block)
{
    m_snake.push_back(block);
    m_velocity.setX(INIT_VELOCITY);
}

void Snake::draw()
{
    for (auto i : m_snake) {
        i->draw();
    }
}

void Snake::update()
{
    handleInput();

    // 每个delay时间移动一次
    if (SDL_GetTicks() - lastMove >= delay) {
        for (auto s = m_snake.end(); s != m_snake.begin() + 1; s--) {
            (*(s - 1))->setPosition((*(s - 2))->getPosition());
        }

        m_snake.front()->setPosition(m_velocity + m_snake.front()->getPosition());

        for (auto i : m_snake) {
            i->update();
        }

        lastMove = SDL_GetTicks();
    }
}

void Snake::clean() {}

void Snake::handleInput()
{
    if (InputHandler::instance()->joysticksInitialised()) {
        if (InputHandler::instance()->xvalue(0, 1) > 0 ||
            InputHandler::instance()->xvalue(0, 1) < 0) {
            m_velocity.setX(1 * InputHandler::instance()->xvalue(0, 1));
        }

        if (InputHandler::instance()->yvalue(0, 1) > 0 ||
            InputHandler::instance()->yvalue(0, 1) < 0) {
            m_velocity.setY(1 * InputHandler::instance()->yvalue(0, 1));
        }

        if (InputHandler::instance()->getButtonState(0, 3)) {
            m_velocity.setX(-1);
        }

        if (InputHandler::instance()->getButtonState(0, 0)) {
            m_velocity.setY(-1);
        }

        if (InputHandler::instance()->getButtonState(0, 1)) {
            m_velocity.setX(1);
        }

        if (InputHandler::instance()->getButtonState(0, 2)) {
            m_velocity.setY(1);
        }
    }

    if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
        if (m_velocity.getX() >= 0) {
            m_velocity.setY(0);
            m_velocity.setX(INIT_VELOCITY);
        }
    }

    if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
        if (m_velocity.getX() <= 0) {
            m_velocity.setY(0);
            m_velocity.setX(-INIT_VELOCITY);
        }
    }

    if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_UP)) {
        if (m_velocity.getY() <= 0) {
            m_velocity.setX(0);
            m_velocity.setY(-INIT_VELOCITY);
        }
    }

    if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
        if (m_velocity.getY() >= 0) {
            m_velocity.setX(0);
            m_velocity.setY(INIT_VELOCITY);
        }
    }
}

SDLGameObject* Snake::front()
{
    return m_snake.front();
}

void Snake::grow(GameObject* newBlock)
{
    m_snake.insert(m_snake.begin(), dynamic_cast<Block*>(newBlock));
    m_snake.front()->setPosition(m_velocity + m_snake.front()->getPosition());
}

bool Snake::notBelong(int x, int y)
{
    for (auto i : m_snake) {
        if ((i->getPosition().getX() == x) && (i->getPosition().getY() == y)) {
            return false;
        }
    }

    return true;
}

bool Snake::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
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

bool Snake::eatSelf()
{
    for (auto i = m_snake.begin() + 1; i != m_snake.end(); i++) {
        if (checkCollision(m_snake.front(), *i)) {
            return true;
        }
    }

    return false;
}

bool Snake::hitWall()
{
    if (m_snake.front()->getPosition().getX() < 0) {
        return true;
    }

    if (m_snake.front()->getPosition().getX() + m_snake.front()->getWidth() > Game::s_screenWidth) {
        return true;
    }

    if (m_snake.front()->getPosition().getY() < 0) {
        return true;
    }

    if (m_snake.front()->getPosition().getY() + m_snake.front()->getHeight() > Game::s_screenHeight) {
        return true;
    }

    return false;
}
