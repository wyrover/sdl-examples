#include "maze.h"
#include <stack>

Maze::Maze(SDL_Renderer *renderer, unsigned int sizeX, unsigned int sizeY, unsigned int cellSize)
    : sizeX(sizeX), sizeY(sizeY), cellSize(cellSize), searchId(1)
{
    // create a blank texture to draw our maze on
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, sizeX, sizeY);
}

Cell *Maze::getCellFromClick(const SDL_Event *event, const SDL_Rect *section)
{
    Point point;
    int clickX = event->button.x;
    int clickY = event->button.y;
    int x = section->x + clickX;
    int y = section->y + clickY;
    point.first = (x / cellSize);
    point.second = (y / cellSize);
    return cells[point];
}

void Maze::createGrid()
{
    cells = {};
    std::vector<Cell *> currentRow = {};
    std::vector<Cell *> previousRow = {};

    // reverse x and y loop order so we can preserve previous row. (could have done previous column as well.)
    for (unsigned int y = cellSize; y < sizeY - cellSize; y += cellSize) {
        Cell *previousCell = nullptr;

        for (unsigned int x = cellSize; x < sizeX - cellSize; x += cellSize) {
            Cell *currentCell = new Cell(x, y, cellSize);

            if (previousCell != nullptr) {
                // connect the two cells on the side.
                previousCell->addNeighbor(currentCell, Cell::RIGHT);
                currentCell->addNeighbor(previousCell, Cell::LEFT);
            }

            currentRow.push_back(currentCell);
            cells[Point(x / cellSize, y / cellSize)] = currentCell;
            previousCell = currentCell;
        }

        for (unsigned int i = 0; i < previousRow.size(); i++) {
            // connect the two cells top and bottom.
            previousRow.at(i)->addNeighbor(currentRow.at(i), Cell::BOTTOM);
            currentRow.at(i)->addNeighbor(previousRow.at(i), Cell::TOP);
        }

        // with the four connections above, this loop only needs to happen once to have all cells connected.
        // clear and reassign our previous row for the next loop.
        previousRow.clear();
        previousRow = currentRow;
        // clear our current row
        currentRow.clear();
    }
}

Cell *Maze::firstCell()
{
    return cells.at(Point(1, 1));
}

bool Maze::createPerfectMaze(SDL_Renderer *renderer)
{
    // setup for our maze creation
    // start at the top
    Cell *currentCell = cells.at(Point(1, 1));
    // we are visiting the current cell. start at 1
    currentCell->setSearchVisitId(searchId);
    // this is used to backtrack once a dead end has been reached.
    std::stack<Cell *> stack;
    unsigned int visited = 1;

    while (visited != cells.size()) {
        // we want to visit every cell once.
        // gather all the cells that we have not visited that are neighbors to this one
        auto neighbors = currentCell->getUnVisitedNeighbors(searchId);

        // when there are *no* unvisted cells left near this one, we've hit a dead end in the maze (likely an edge)
        if (!neighbors.size()) {
            if (stack.empty()) {
                // the grid is invalid.
                return false;
            }

            // retrace our steps (this can happen many times if every neighbor has been visited)
            currentCell = stack.top();
            stack.pop();
            continue;
        }

        // we have unvisted neighbors! retain the current cell so we can rewind later.
        stack.push(currentCell);
        // grab a random neighbor
        Cell *neighborCell = neighbors[rand() % neighbors.size()];
        visited++;
        // mark it as visited, remove the wall between the two cells, and make our neighbor the current cell.
        neighborCell->setSearchVisitId(searchId);
        neighborCell->removeWall(currentCell);
        currentCell->removeWall(neighborCell);
        currentCell = neighborCell;
    }

    SDL_Texture *currentTarget = SDL_GetRenderTarget(renderer);
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0);
    SDL_RenderClear(renderer);

    for (auto &kv : cells) {
        kv.second->render(renderer);
    }

    SDL_SetRenderTarget(renderer, currentTarget);
    return true;
}

std::deque<Cell *> Maze::dfsSearch(Cell *start, Cell *end)
{
    bool found = false;
    auto currentCell = start;
    searchId++;
    std::deque<Cell *> stack;

    while (!found) {
        auto neighbors = currentCell->getUnVisitedAttachedNeighbors(searchId);

        if (!neighbors.size()) {
            if (stack.empty()) {
                break;
            }

            currentCell = stack.front();
            stack.pop_front();
            continue;
        }

        stack.push_front(currentCell);
        Cell *neighborCell = neighbors[rand() % neighbors.size()];
        neighborCell->setSearchVisitId(searchId);
        currentCell = neighborCell;

        if (currentCell == end) {
            found = true;
        }
    }

    if (stack.size()) {
        stack.push_front(end);
    }

    return stack;
}

void Maze::render(SDL_Renderer *renderer, SDL_Rect *section)
{
    SDL_RenderCopy(renderer, texture, section, NULL);
}