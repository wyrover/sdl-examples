// 捕获各类输入事件

#ifndef __INPUT_HANDLER_H__
#define __INPUT_HANDLER_H__
#include "SDL.h"

#include <vector>

#include "vector2d.h"
#include <iostream>

enum mouse_buttons {
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler
{
public:
    static InputHandler* instance()
    {
        if (s_pInstance == nullptr) {
            s_pInstance = new InputHandler();
        }

        return s_pInstance;
    }
    void update();
    void clean();
    void initialiseJoysticks();
    bool joysticksInitialised()
    {
        return m_bJoysticksInitialised;
    }

    // @joy 手柄号
    // @stick 摇杆号
    int xvalue(int joy, int stick);
    int yvalue(int joy, int stick);

    bool getButtonState(int joy, int buttonNumber)
    {
        return m_buttonStates[joy][buttonNumber];
    }

    bool getMouseButtonState(int buttonNumber)
    {
        return m_mouseButtonStates[buttonNumber];
    }

    Vector2D* getMousePosition()
    {
        return m_mousePosition;
    }

    bool isKeyDown(SDL_Scancode key);

    // reset mouse button
    void reset();
private:
    InputHandler() {};
    ~InputHandler() {}
    static InputHandler* s_pInstance;
    std::vector<SDL_Joystick*> m_joysticks;
    bool m_bJoysticksInitialised;

    // 两个vector2d代表两个摇杆
    std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
    std::vector<std::vector<bool>> m_buttonStates;

    const int m_joystickDeadZone = 10000;
    std::vector<bool> m_mouseButtonStates;
    Vector2D* m_mousePosition;
    const Uint8* m_keystates = SDL_GetKeyboardState(nullptr);

    // private functions to handle different event types
    // handle keyboard events
    void onKeyDown();
    void onKeyUp();
    // handle mouse events
    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);

    // handle joysticks events
    void onJoystickAxisMove(SDL_Event& event);
    void onJoystickButtonDown(SDL_Event& event);
    void onJoystickButtonUp(SDL_Event& event);

};
#endif
