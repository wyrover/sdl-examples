#include "SDL.h"
#include "cell.h"
#include "SDL_circle.h"
Cell::Cell(int x, int y, int size) : x(x), y(y), size(size), walls {1, 1, 1, 1}, searchVisitId(0)
{
    red   = (Uint8)(rand() % 150);
    green = (Uint8)(rand() % 150);
    blue  = (Uint8)(rand() % 150);
    alpha = (Uint8)255;
    neighbors = {nullptr, nullptr, nullptr, nullptr};
    wallSize = 2;
}

void Cell::drawCircle(SDL_Renderer *renderer, SDL_Rect *mazeRect) const
{
    SDL_RenderFillCircle(renderer,  x - mazeRect->x, y - mazeRect->y, size / 2);
}

void Cell::renderSelected(SDL_Renderer *renderer, SDL_Rect *mazeRect) const
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    drawCircle(renderer, mazeRect);
}

void Cell::render(SDL_Renderer *renderer) const
{
    SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
    SDL_Rect rects[4] = {};
    int rectCount = 0;

    if (walls[0]) {
        // top wall.
        rects[rectCount++] = {
            x, y,
            size, wallSize,
        };
    }

    if (walls[1]) {
        // right wall.
        rects[rectCount++] = {
            x + size, y,
            wallSize, size,
        };
    }

    if (walls[2]) {
        // bottom wall.
        rects[rectCount++] = {
            x, y + size,
            size, wallSize,
        };
    }

    if (walls[3]) {
        // left wall.
        rects[rectCount++] = {
            x, y,
            wallSize, size,
        };
    }

    SDL_RenderFillRects(renderer, rects, rectCount);
}

void Cell::addNeighbor(Cell *neighbor, int direction)
{
    neighbors[direction] = neighbor;
}

void Cell::setSearchVisitId(unsigned int visitId)
{
    searchVisitId = visitId;
}

bool Cell::isVisited(unsigned int searchId) const
{
    return searchVisitId == searchId;
}

std::vector<Cell*> Cell::getUnVisitedNeighbors(unsigned int searchId) const
{
    std::vector<Cell *> unvisited;

    for (Cell *c : neighbors) {
        if (c == NULL || c->isVisited(searchId)) {
            continue;
        }

        unvisited.push_back(c);
    }

    return unvisited;
}

std::vector<Cell *> Cell::getUnVisitedAttachedNeighbors(unsigned int searchId) const
{
    std::vector<Cell *> unvisitedAttached;

    for (auto n : attachedNeighbors) {
        if (n->isVisited(searchId)) {
            continue;
        }

        unvisitedAttached.push_back(n);
    }

    return unvisitedAttached;
}

void Cell::removeWall(const Cell *neighbor)
{
    for (unsigned int i = 0; i < neighbors.size(); i++) {
        if (neighbors[i] == NULL || neighbors[i] != neighbor) {
            continue;
        }

        attachedNeighbors.push_back(neighbors[i]);
        walls[i] = 0;
        break;
    }
}

Cell *Cell::getAttachedNeighbor(unsigned int direction) const
{
    auto n = neighbors[direction];

    for (Cell *c : attachedNeighbors) {
        if (n == c) {
            return c;
        }
    }

    return nullptr;
}
