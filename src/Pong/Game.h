// ------------------------------------------------------------
// Porting Pong From Flash To C++
// http://rembound.com/articles/porting-pong-from-flash-to-cpp
// (c) 2014 Rembound.com
// ------------------------------------------------------------

#ifndef GAME_H_
#define GAME_H_

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

#include "Board.h"
#include "Paddle.h"
#include "Ball.h"

#define FPS_DELAY 500
#define AI_SPEED 400 // Pixels per second

class Game {
public:
    Game();
    ~Game();

    bool Init();
    void Run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    // Timing
    unsigned int lasttick, fpstick, fps, framecount;

    Board* board;
    std::vector<Paddle*> paddle;
    Ball* ball;

    void Clean();
    void Update(float delta);
    void Render(float delta);

    void NewGame();

    void SetPaddleY(int index, float y);
    void CheckCollisions();
    float GetReflection(int index, float hity);

    void AI(float delta);
};

#endif
