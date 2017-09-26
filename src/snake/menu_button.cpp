#include "menu_button.h"
#include "input_handler.h"

MenuButton::MenuButton() : SDLGameObject()
{
}

void MenuButton::draw()
{
    SDLGameObject::draw(); // use the base class drawing
}

void MenuButton::update()
{
    Vector2D* pMousePos = InputHandler::instance()->getMousePosition();

    if (pMousePos->getX() < (m_position.getX() + m_width)
        && pMousePos->getX() > m_position.getX()
        && pMousePos->getY() < (m_position.getY() + m_height)
        && pMousePos->getY() > m_position.getY()) {
        if (InputHandler::instance()->getMouseButtonState(LEFT) && m_bReleased) {
            m_currentFrame = CLICKED;
            m_callback();
            m_bReleased = false;
        } else if (!InputHandler::instance()->getMouseButtonState(LEFT)) {
            m_bReleased = true;
            m_currentFrame = MOUSE_OVER;
        }
    } else {
        m_currentFrame = MOUSE_OUT;
    }
}


void MenuButton::clean()
{
    SDLGameObject::clean();
}

void MenuButton::load(const LoaderParams* pParams)
{
    SDLGameObject::load(pParams);
    m_callbackID = pParams->getCallbackID();
    m_currentFrame = MOUSE_OVER;
}
