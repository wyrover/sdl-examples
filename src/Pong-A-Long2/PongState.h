#ifndef PongState_h__
#define PongState_h__
#pragma once

#include "GameApp.h"
#include "Texture.h"
#include "Vec2D.h"
#include "GameState.h"
#include "GameObject.h"
#include "SoundEffect.h"


//enum DIRN { LESSTHAN, GRTERTHAN};
enum BALL_DIRN { LEFT, RIGHT};

class PongState : public GameState
{
public:
    PongState();
    virtual ~PongState();

    bool Initialise();
    void CleanUp();
    void Render(Renderer& renderer);
    void Update(double dt);
    GameState::QUITRESPONSE QuitDialog();

    bool CreateBall(Renderer& renderer);
    bool CreateSounds();
    bool CreatePaddle(GameObject &paddle, Renderer& renderer, int paddle_x, int paddle_y);


    bool OnKeyDown(SDL_Scancode scan, SDL_Keycode key);
    bool OnKeyUp(SDL_Scancode scan, SDL_Keycode key);

private:
    void ResetBall(BALL_DIRN dirn);

    bool CheckForBallPaddleCollision(int Norm, GameObject& paddle_obj, GameObject& ball_obj, double circle_radius);

    bool PaddleFaceCollide(GameObject &paddle_obj, GameObject &ball_obj, int Norm, double planePos, double circle_radius);

    bool PaddleCornerCollide(GameObject &ball_obj, GameObject &paddle_obj, int Norm, int dirn, double circle_radius);

    bool BallBounceOffPaddle(int Norm, double dist, GameObject &ball_obj, double relativeYPosition);

    void PaddleClamp(double dt, GameObject& paddle);

    void CheckForPointWon();

    void UpdateScores();

    void TestForWallCollisions();

    GameObject m_Ball;
    GameObject m_LeftPaddle;
    GameObject m_RightPaddle;

    Texture m_LeftScoreText;
    Texture m_RightScoreText;

    SoundEffect m_BounceSound;
    SoundEffect m_ScoreSound;

    double m_Ball_XSpeed = 200.;
    double m_BounceModifier = m_Ball_XSpeed * 1.5;

    int m_paddle_min = 50;
    int m_paddle_max = -m_paddle_min; // Redefined in AppInit
    double m_paddle_speed = 200.0;

    int m_LeftPlayerScore = 0;
    int m_RightPlayerScore = 0;
};

#endif // PongState_h__

