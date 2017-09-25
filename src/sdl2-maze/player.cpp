#include "player.h"
#include "SDL_circle.h"

Player::Player(SDL_Renderer *r, Trail *trail, Cell *cell) : renderer(r), trail(trail), currentCell(cell)
{
    keyDown = 0;
}

Cell *Player::getCellForKey(int key) const
{
    switch (key) {
    case SDLK_UP:
        return currentCell->getAttachedNeighbor(Cell::TOP);

    case SDLK_DOWN:
        return currentCell->getAttachedNeighbor(Cell::BOTTOM);

    case SDLK_RIGHT:
        return currentCell->getAttachedNeighbor(Cell::RIGHT);

    case SDLK_LEFT:
        return currentCell->getAttachedNeighbor(Cell::LEFT);

    default:
        break;
    }

    return nullptr;
}

void Player::moveToCell(Cell *moveCell)
{
    if (moveCell != nullptr) {
        keyTimeout = SDL_GetTicks() + 25;
        trail->addCell(renderer, currentCell);
        currentCell = moveCell;
    }
}

void Player::handleEvent(SDL_Event *e)
{
    switch (e->type) {
    case SDL_KEYDOWN: {
        keyDown = e->key.keysym.sym;
        moveToCell(getCellForKey(keyDown));
        break;
    }

    case SDL_KEYUP: {
        if (e->key.keysym.sym == keyDown) {
            keyDown = 0;
        }
    }

    default:
        break;
    }

    if (keyDown && SDL_TICKS_PASSED(SDL_GetTicks(), keyTimeout)) {
        moveToCell(getCellForKey(keyDown));
    }
}

void Player::render(SDL_Rect *section) const
{
    SDL_SetRenderDrawColor(renderer, 100, 255, 100, 255);
    SDL_RenderFillCircle(renderer,  currentCell->getX() - section->x, currentCell->getY() - section->y, currentCell->getSize() / 2);
}