#ifndef _MAZE_MAZE_H_
#define _MAZE_MAZE_H_
#include <map>
#include <deque>
#include <SDL.h>
#include "cell.h"

typedef std::pair<int, int> Point;
class Maze
{
protected:
    std::map<Point, Cell *> cells;
    // the size of this maze.
    unsigned int sizeX;
    unsigned int sizeY;
    // the size of the cells in the maze.
    unsigned int cellSize;
    // the current search id. incremented on each search
    unsigned int searchId;
    // the texture this maze is drawn on. the main renderer draws this texture.
    SDL_Texture *texture;
public:
    Maze(SDL_Renderer *renderer, unsigned int sizeX, unsigned int sizeY, unsigned int cellSize);
    /**
    * this creates a grid of square cells. cells are connected on their four edges
    */
    void createGrid();
    Cell *firstCell();
    /**
    * create the full "perfect maze" and render it to a texture
    */
    bool createPerfectMaze(SDL_Renderer *renderer);
    /**
    * render all of our cells. The cells handle the rendering
    */
    void render(SDL_Renderer *renderer, SDL_Rect *section);
    /**
    * gets the cell the click happened on, translating the screen coords to cell coords
    */
    Cell *getCellFromClick(const SDL_Event *event, const SDL_Rect *section);
    /**
    * find a path between two points using DFS
    */
    std::deque<Cell *> dfsSearch(Cell *start, Cell* end);
};

#endif