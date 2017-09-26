#include "Font_TTF.h"

#include <SDL_ttf.h>


FontTTF::FontTTF()
{
    m_textColor = { 0x00, 0x00, 0x00, 0x00 };
}

FontTTF::~FontTTF()
{
    Release();
}

bool FontTTF::LoadFont(const char* file, int ptsize, SDL_Color textColor)
{
    m_pFont = TTF_OpenFont(file, ptsize);

    if (m_pFont == nullptr) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Font not loaded", nullptr);
        m_ptsize = 0;
        return false;
    }

    m_ptsize = ptsize;
    m_textColor = textColor;
    return true;
}

void FontTTF::Release()
{
    TTF_CloseFont(m_pFont);
    m_pFont = nullptr;
    m_ptsize = 0;
}
