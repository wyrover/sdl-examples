#ifndef _MAZE_CELL_H
#define _MAZE_CELL_H
#include <vector>

class Cell
{
protected:
    int x;
    int y;
    int size;
    int walls[4];
    unsigned int searchVisitId;
    int wallSize;
    Uint8 red;
    Uint8 green;
    Uint8 blue;
    Uint8 alpha;
    std::vector<Cell*> neighbors;
    std::vector<Cell*> attachedNeighbors;
public:
    Cell(int x, int y, int size);
    void render(SDL_Renderer *renderer) const;
    void drawCircle(SDL_Renderer *renderer, SDL_Rect *mazeRect) const;
    void renderSelected(SDL_Renderer *renderer, SDL_Rect *mazeRect) const;
    void addNeighbor(Cell *neighbor, int direction);
    void setSearchVisitId(unsigned int visitId);
    bool isVisited(unsigned int searchId) const;

    std::vector<Cell *> getUnVisitedNeighbors(unsigned int searchId) const;
    std::vector<Cell *> getUnVisitedAttachedNeighbors(unsigned int searchId) const;
    void removeWall(const Cell *neighbor);

    int getX() const
    {
        return x;
    }
    int getY() const
    {
        return y;
    }
    int getSize() const
    {
        return size;
    }

    Cell *getAttachedNeighbor(unsigned int direction) const;

    const static int TOP    = 0;
    const static int RIGHT  = 1;
    const static int BOTTOM = 2;
    const static int LEFT   = 3;
};

#endif