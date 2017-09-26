// ------------------------------------------------------------
// Porting Pong From Flash To C++
// http://rembound.com/articles/porting-pong-from-flash-to-cpp
// (c) 2014 Rembound.com
// ------------------------------------------------------------

#include "Board.h"

Board::Board(SDL_Renderer* renderer): Entity(renderer)
{
    SDL_Surface* surface = IMG_Load("pong/assets/side.png");
    sidetexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    srand(time(0));
    x = 0;
    y = 0;
    width = 800;
    height = 600;
    // Define bounds
    boundtop = 21;
    boundbottom = 600 - 21;
}

Board::~Board()
{
    // Clean resources
    SDL_DestroyTexture(sidetexture);
}

void Board::Update(float delta)
{
}

void Board::Render(float delta)
{
    // Render top and bottom
    SDL_Rect dstrect;
    dstrect.x = 0;
    dstrect.y = 0;
    dstrect.w = 800;
    dstrect.h = 21;
    SDL_RenderCopy(renderer, sidetexture, 0, &dstrect);
    dstrect.x = 0;
    dstrect.y = 600 - 21;
    dstrect.w = 800;
    dstrect.h = 21;
    SDL_RenderCopy(renderer, sidetexture, 0, &dstrect);
}

