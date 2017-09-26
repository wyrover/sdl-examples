#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

#include <string>
#include <SDL.h>
#include <map>

class TextureManager
{
public:
    bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);
    void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer,
              SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawFrame(std::string id, int x, int y, int width, int height, int currentRow,
                   int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void clearFromTextureMap(std::string id);

    std::map<std::string, SDL_Texture*> m_textureMap;
    static TextureManager* s_pInstance;

    static TextureManager* instance();

private:
    TextureManager() {}

};



#endif
