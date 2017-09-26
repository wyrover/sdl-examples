#include "PongState.h"

#include "Collision.h"
#include "Font_TTF.h"

PongState::PongState() : GameState()
{
}

PongState::~PongState()
{
    CleanUp();
}

bool PongState::Initialise()
{
    SDL_assert(m_pWnd);
    Renderer& renderer = m_pWnd->GetRenderer();

    if (!CreateSounds())
        return false;

    if (!CreateBall(renderer))
        return false;

    m_paddle_max = m_pWnd->GetHeight() - m_paddle_min;
    int paddle_y = m_pWnd->GetHeight() / 2;

    if (!CreatePaddle(m_LeftPaddle, renderer, 20, paddle_y))
        return false;

    if (!CreatePaddle(m_RightPaddle, renderer, m_pWnd->GetWidth() - 20, paddle_y))
        return false;

    UpdateScores();
    return true;
}

bool PongState::CreateBall(Renderer& renderer)
{
    if (!m_Ball.CreateTexture(renderer, "Pong-A-Long2/assets/ball.png"))
        return false;

    m_Ball.SetAnchorPt(GameObject::CENTRE);
    ResetBall(LEFT);
    return true;
}

void PongState::ResetBall(BALL_DIRN dirn)
{
    double x = m_pWnd->GetWidth() / 2;
    double y = m_pWnd->GetHeight() / 2;
    double vx = (dirn == RIGHT) ? m_Ball_XSpeed : -m_Ball_XSpeed;
    m_Ball.SetVelocity(Vec2D(vx, 0));
    m_Ball.SetPosition(Vec2D(x, y));
}

bool PongState::CreateSounds()
{
    if (!m_BounceSound.CreateFromFile("Pong-A-Long2/assets/Bounce.wav"))
        return false;

    if (!m_ScoreSound.CreateFromFile("Pong-A-Long2/assets/Score.wav"))
        return false;

    return true;
}

bool PongState::CreatePaddle(GameObject &paddle, Renderer& renderer, int paddle_x, int paddle_y)
{
    // Left paddle creation
    if (!paddle.CreateTexture(renderer, "Pong-A-Long2/assets/paddle.png"))
        return false;

    paddle.SetAnchorPt(GameObject::CENTRE);
    paddle.SetPosition(Vec2D(paddle_x, paddle_y));
    return true;
}

void PongState::CleanUp()
{
}


void PongState::Render(Renderer& renderer)
{
    // Set Score text positions
    static int left_x = 4 * m_pWnd->GetWidth() / 10;
    static int right_x = 6 * m_pWnd->GetWidth() / 10;
    m_Ball.Render(renderer);
    m_LeftPaddle.Render(renderer);
    m_RightPaddle.Render(renderer);
    m_LeftScoreText.Render(renderer, left_x  - m_LeftScoreText.GetWidth(), 0);
    m_RightScoreText.Render(renderer, right_x, 0);
}

void PongState::Update(double dt)
{
    // Move game objects
    m_Ball.Update(dt);
    m_LeftPaddle.Update(dt);
    m_RightPaddle.Update(dt);
    // Clamp paddles to stay onscreen
    PaddleClamp(dt, m_LeftPaddle);
    PaddleClamp(dt, m_RightPaddle);

    if (CheckForBallPaddleCollision(1, m_LeftPaddle, m_Ball, m_Ball.GetWidth() / 2) ||
        CheckForBallPaddleCollision(-1, m_RightPaddle, m_Ball, m_Ball.GetWidth() / 2))
        m_BounceSound.Play();

    TestForWallCollisions();
    CheckForPointWon();
}


GameState::QUITRESPONSE PongState::QuitDialog()
{
    return ThreeOptionQuitDialog("MENUSTATE");
}

void PongState::CheckForPointWon()
{
    if (CheckForCircleAxisIntersection(XAXIS, 1, -m_Ball.GetWidth(), m_Ball, m_Ball.GetWidth() / 2)) {
        m_RightPlayerScore++;
        ResetBall(RIGHT);
        UpdateScores();
        m_ScoreSound.Play();
    } else if (CheckForCircleAxisIntersection(XAXIS, -1, m_pWnd->GetWidth() + m_Ball.GetWidth(), m_Ball, m_Ball.GetWidth() / 2)) {
        m_LeftPlayerScore++;
        ResetBall(LEFT);
        UpdateScores();
        m_ScoreSound.Play();
    }
}

void PongState::UpdateScores()
{
    Renderer& renderer = m_pWnd->GetRenderer();
    FontTTF arialFont;

    if (!arialFont.LoadFont("C:\\Windows\\Fonts\\ARIAL.TTF", 50, SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF }))
        return;
    m_LeftScoreText.CreateFromText(renderer, std::to_string(m_LeftPlayerScore), arialFont);
    m_RightScoreText.CreateFromText(renderer, std::to_string(m_RightPlayerScore), arialFont);
}

void PongState::TestForWallCollisions()
{
    if (CheckForCircleAxisCollision(YAXIS, 1, 0, m_Ball, m_Ball.GetHeight() / 2) ||
        CheckForCircleAxisCollision(YAXIS, -1, m_pWnd->GetHeight(), m_Ball, m_Ball.GetHeight() / 2))
        m_BounceSound.Play();
}

bool PongState::CheckForBallPaddleCollision(int Norm, GameObject& paddle_obj, GameObject& ball_obj, double circle_radius)
{
    double paddle_halfwidth = paddle_obj.GetWidth() / 2;
    double planePos = paddle_obj.GetPos().x + Norm * paddle_halfwidth;

    // If ball passes through the plane in line with the paddle
    if (CheckForCircleAxisIntersection(XAXIS, Norm, planePos, ball_obj, circle_radius)) {
        if (PaddleFaceCollide(paddle_obj, ball_obj, Norm, planePos, circle_radius))
            return true;

        // Check for corner collisions
        // Bottom corner
        if (PaddleCornerCollide(ball_obj, paddle_obj, Norm, 1, circle_radius))
            return true;

        // Top corner
        if (PaddleCornerCollide(ball_obj, paddle_obj, Norm, -1, circle_radius))
            return true;
    }

    return false;
}



bool PongState::PaddleFaceCollide(GameObject &paddle_obj, GameObject &ball_obj, int Norm, double planePos, double circle_radius)
{
    double paddle_halfheight = paddle_obj.GetHeight() / 2;
    double& velocity_x = ball_obj.GetVel().x;
    double dist = GetIntersectionDist(XAXIS, Norm, planePos, ball_obj, circle_radius);
    double timeSinceCollision = abs(dist / velocity_x);
    // Find the balls y position relative to paddle centre at time of collision, scaled to half height of paddle
    double relativeYVelocity = ball_obj.GetVel().y - paddle_obj.GetVel().y;
    double relativeYPosition = (ball_obj.GetPos().y - relativeYVelocity * timeSinceCollision - paddle_obj.GetPos().y) / paddle_halfheight;

    // Bounce if hit paddle face
    if (relativeYPosition >= -1 && relativeYPosition <= 1)
        return BallBounceOffPaddle(Norm, dist, ball_obj, relativeYPosition);

    return false;
}

bool PongState::PaddleCornerCollide(GameObject &ball_obj, GameObject &paddle_obj, int Norm, int dirn, double circle_radius)
{
    double& position_x = ball_obj.GetPos().x;
    double& velocity_x = ball_obj.GetVel().x;
    double paddle_halfheight = paddle_obj.GetHeight() / 2;
    double paddle_halfwidth = paddle_obj.GetWidth() / 2;
    Vec2D corner_offset(paddle_halfwidth * Norm, dirn * paddle_halfheight);
    double timeSinceCollision = CheckCornerCircleCollision(paddle_obj.GetPos() + corner_offset, ball_obj.GetPos(), ball_obj.GetVel() - paddle_obj.GetVel(), circle_radius);

    if (timeSinceCollision >= 0.0)
        return BallBounceOffPaddle(Norm, timeSinceCollision * velocity_x, ball_obj, dirn);

    return false;
}

bool PongState::BallBounceOffPaddle(int Norm, double dist, GameObject &ball_obj, double relativeYPosition)
{
    double& position_x = ball_obj.GetPos().x;
    double& velocity_x = ball_obj.GetVel().x;
    velocity_x = -velocity_x;
    position_x = position_x - 2 * Norm * dist;
    // Add a y component depending on position relative to paddle centre
    ball_obj.GetVel().y = relativeYPosition * m_BounceModifier;
    return true;
}

void PongState::PaddleClamp(double dt, GameObject& paddle)
{
    double& y = paddle.GetPos().y;

    if (y < m_paddle_min)
        y = m_paddle_min;

    if (y > m_paddle_max)
        y = m_paddle_max;
}

bool PongState::OnKeyDown(SDL_Scancode scan, SDL_Keycode key)
{
    switch (key) {
    case SDLK_w:
        m_LeftPaddle.SetVelocity(Vec2D(0, -m_paddle_speed));
        break;

    case SDLK_s:
        m_LeftPaddle.SetVelocity(Vec2D(0, m_paddle_speed));
        break;

    case  SDLK_UP:
        m_RightPaddle.SetVelocity(Vec2D(0, -m_paddle_speed));
        break;

    case SDLK_DOWN:
        m_RightPaddle.SetVelocity(Vec2D(0, m_paddle_speed));
        break;
    }

    return true;
}

bool PongState::OnKeyUp(SDL_Scancode scan, SDL_Keycode key)
{
    double& leftVertSpeed = m_LeftPaddle.GetVel().y;
    double& rightVertSpeed = m_RightPaddle.GetVel().y;

    switch (key) {
    case SDLK_w:
        if (leftVertSpeed < 0.0)
            leftVertSpeed = 0.0;

        break;

    case SDLK_s:
        if (leftVertSpeed > 0.0)
            leftVertSpeed = 0.0;

        break;

    case  SDLK_UP:
        if (rightVertSpeed < 0.0)
            rightVertSpeed = 0.0;

        break;

    case SDLK_DOWN:
        if (rightVertSpeed > 0.0)
            rightVertSpeed = 0.0;

        break;

    case SDLK_ESCAPE:
        RequestAppQuit();
        break;
    }

    return true;
}


