#ifndef Window_h__
#define Window_h__
#pragma once

#include <string>
#include <SDL.h>
#include "Renderer.h"
#include "EventHandler.h"

class Window : public EventHandler
{
public:
    Window();
    ~Window();

    void Release();

    bool Create(std::string title, int x, int y, int w, int h, Uint32 flags);
    bool CreateRenderer(Uint32 iFlags = SDL_RENDERER_ACCELERATED);
    void ClearWindow();
    void Present();

    int GetID()
    {
        return m_WindowID;
    }

    int GetHeight()
    {
        return m_Height;
    }
    int GetWidth()
    {
        return m_Width;
    }

    void SetTitle(std::string NewTitle)
    {
        SDL_SetWindowTitle(m_pWindow, NewTitle.c_str());
    }

    bool CanRender()
    {
        return (m_pWindow && m_Renderer.GetRenderPtr() && !m_bMinimized);
    }

    Renderer& GetRenderer()
    {
        return m_Renderer;
    }

    //Window focii
    bool hasMouseFocus()
    {
        return m_bMouseFocus;
    }
    bool hasKeyboardFocus()
    {
        return m_bKeyboardFocus;
    }
    bool isMinimized()
    {
        return m_bMinimized;
    }
    bool isMaximized()
    {
        return m_bMaximized;
    }
    bool isShown()
    {
        return m_bShown;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Event Handlers
    virtual bool OnShow(int windowID)
    {
        m_bShown = true;
        return true;
    }
    virtual bool OnHide(int windowID)
    {
        m_bShown = false;
        return true;
    }

    virtual bool OnExpose(int windowID)
    {
        return true;
    }

    virtual bool OnResize(int windowID, int w, int h)
    {
        m_Width = w;
        m_Height = h;
        return true;
    }

    virtual bool OnMinimize(int windowID)
    {
        m_bMinimized = true;
        m_bMaximized = false;
        return true;
    }

    virtual bool OnMaximize(int windowID)
    {
        m_bMinimized = false;
        m_bMaximized = true;
        return true;
    }

    virtual bool OnRestore(int windowID)
    {
        m_bMinimized = false;
        m_bMaximized = false;
        return true;
    }

    virtual bool OnMouseFocus(int windowID)
    {
        m_bMouseFocus = true;
        return true;
    }

    virtual bool OnMouseBlur(int windowID)
    {
        m_bMouseFocus = false;
        return true;
    }

    virtual bool OnKeyFocus(int windowID)
    {
        m_bKeyboardFocus = true;
        return true;
    }

    virtual bool OnKeyBlur(int windowID)
    {
        m_bKeyboardFocus = false;
        return true;
    }

private:
    SDL_Window* m_pWindow = nullptr;
    Renderer m_Renderer;

    int m_WindowID = 0;
    int m_Width = 0;
    int m_Height = 0;

    //Window state
    bool m_bMouseFocus = false;
    bool m_bKeyboardFocus = false;
    bool m_bFullScreen = false;
    bool m_bMinimized = false;
    bool m_bMaximized = false;
    bool m_bShown = false;
};

#endif // Window_h__
