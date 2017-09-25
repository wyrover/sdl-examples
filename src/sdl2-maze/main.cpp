#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <stack>
#include "maze.h"
#include "trail.h"
#include "player.h"

using namespace std;

int main()
{
    // seed rand so we don't get the same maze over and over
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO);
    unsigned int cellSize = 32;
    unsigned int mazeSizeX = 1024;
    unsigned int mazeSizeY = 768;
    SDL_Rect windowRect = {
        0,
        0,
        1024,
        768
    };
    SDL_Window *w = SDL_CreateWindow("maze!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowRect.w, windowRect.h, 0);
    SDL_Renderer *r = SDL_CreateRenderer(w, 0, 0);
    bool running = true;
    unsigned long frames = 0;
    double totalTime = 0.0;
    Maze maze(r, mazeSizeX, mazeSizeY, cellSize);
    maze.createGrid();

    if (!maze.createPerfectMaze(r)) {
        std::cout << "Failed to create maze." << std::endl;
        return 1;
    }

    SDL_Rect mazeRect = windowRect;
    Trail trail(r, mazeSizeX, mazeSizeY);
    bool isCellSelection = false;
    Cell *selectedCell = nullptr;
    Player player(r, &trail, maze.firstCell());
    std::deque<Cell *> trailCells;
    unsigned int trailTimeout = 0;

    while (running) {
        SDL_Event e;

        while (SDL_PollEvent(&e)) {
            player.handleEvent(&e);

            switch (e.type) {
            case SDL_QUIT:
                running = false;
                break;

            case SDL_KEYUP:
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    selectedCell = nullptr;
                }

                break;

            case SDL_MOUSEBUTTONDOWN:
                isCellSelection = true;
                break;

            case SDL_MOUSEMOTION:
                if (e.motion.state ^ SDL_BUTTON_LMASK) {
                    break;
                }

                mazeRect.x += e.motion.xrel;
                mazeRect.y += e.motion.yrel;
                mazeRect.x = max(0, min(mazeRect.x, (int)mazeSizeX - mazeRect.w));
                mazeRect.y = max(0, min(mazeRect.y, (int)mazeSizeY - mazeRect.h));
                isCellSelection = false;
                break;

            case SDL_MOUSEBUTTONUP: {
                if (!isCellSelection) {
                    break;
                }

                selectedCell = maze.getCellFromClick(&e, &mazeRect);

                if (selectedCell == player.getCell()) {
                    selectedCell = nullptr;
                }

                trailCells = maze.dfsSearch(player.getCell(), selectedCell);
                break;
            }

            default:
                break;
            }
        }

        time_t start;
        time(&start);
        SDL_SetRenderTarget(r, NULL);
        SDL_SetRenderDrawColor(r, 200, 200, 200, 0);
        SDL_RenderClear(r);
        maze.render(r, &mazeRect);
        trail.render(r, &mazeRect);

        if (SDL_TICKS_PASSED(SDL_GetTicks(), trailTimeout) && trailCells.size()) {
            trailTimeout = SDL_GetTicks() + 75;
            trail.addCell(r, player.getCell());
            player.setCell(trailCells.back());
            trailCells.pop_back();

            if (!trailCells.size()) {
                selectedCell = nullptr;
            }
        }

        player.render(&mazeRect);

        if (selectedCell != nullptr) {
            selectedCell->renderSelected(r, &mazeRect);
        }

        SDL_RenderPresent(r);
        time_t end;
        time(&end);
        totalTime += end - start;
        frames++;
    }

    std::cout << (totalTime / frames) << std::endl;
    return 0;
}