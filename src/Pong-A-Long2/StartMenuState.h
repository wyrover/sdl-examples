#ifndef StartMenuState_h__
#define StartMenuState_h__
#pragma once

#include "GameState.h"
#include "Texture.h"

class StartMenuState : public GameState
{
public:
    StartMenuState() {}
    ~StartMenuState() {}

    bool Initialise();
    void CleanUp();
    void Render(Renderer& renderer);
    void Update(double dt);
    virtual QUITRESPONSE QuitDialog();

    bool OnKeyDown(SDL_Scancode scan, SDL_Keycode key);

private:
    Texture m_MenuText;
    Texture m_Choice1Text;
    Texture m_Choice2Text;
};



#endif  StartMenuState_h__
