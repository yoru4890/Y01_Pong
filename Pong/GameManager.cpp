#include "GameManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Ball.h"
#include "Constants.h"

HRESULT GameManager::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height)
{
    HRESULT hr;
    hr = D2DFramework::Initialize(hInstance, title, width, height);
    ThrowIfFailed(hr, "Failed in D2DFramework::Initailize()");
    
    const D2D_POINT_2F WALL_TOP_LEFT { GameConstants::TOP_LEFT_X, GameConstants::TOP_LEFT_Y };
    const D2D_POINT_2F WALL_BOTTOM_RIGHT { GameConstants::BOTTOM_RIGHT_X, GameConstants::BOTTOM_RIGHT_Y};

    for (float x = WALL_TOP_LEFT.x; x <= WALL_BOTTOM_RIGHT.x; x++)
    {
        mWalls.push_back(std::make_shared<Actor>(this, L"Images/wall.png", x, WALL_TOP_LEFT.y));
        mWalls.push_back(std::make_shared<Actor>(this, L"Images/wall.png", x, WALL_BOTTOM_RIGHT.y));
    }
    
    for (float y = WALL_TOP_LEFT.y; y <= WALL_BOTTOM_RIGHT.y; y++)
    {
        mWalls.push_back(std::make_shared<Actor>(this, L"Images/wall.png", WALL_TOP_LEFT.x, y));
        mWalls.push_back(std::make_shared<Actor>(this, L"Images/wall.png", WALL_BOTTOM_RIGHT.x, y));
    }

    for (float y = WALL_TOP_LEFT.y; y <= WALL_BOTTOM_RIGHT.y; y += GameConstants::MIDDLE_WALL_GAP)
    {
        mWalls.push_back(std::make_shared<Actor>(this, L"Images/wall.png", (WALL_TOP_LEFT.x + WALL_BOTTOM_RIGHT.x)/2, y));
    }

    mPlayerBar = std::make_shared<Player>(this);
    mEnemyBar = std::make_shared<Enemy>(this);

    mBall = std::make_shared<Ball>(this);

    return S_OK;
}

void GameManager::Render()
{
    mspRenderTarget->BeginDraw();
    mspRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
    mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f));

    for (auto& wall : mWalls)
    {
        wall->Draw();
    }

    CheckInput();

    mPlayerBar->Draw();
    mEnemyBar->Draw();
    mBall->Draw();

    HRESULT hr = mspRenderTarget->EndDraw();

    if (hr == D2DERR_RECREATE_TARGET)
    {
        CreateDeviceResources();
    }
}

void GameManager::Release()
{
    mBall.reset();
    mEnemyBar.reset();
    mPlayerBar.reset();
    mWalls.clear();

    D2DFramework::Release();
}

void GameManager::CheckInput()
{
    Player* p = static_cast<Player*>(mPlayerBar.get());
    Enemy* pE = static_cast<Enemy*>(mEnemyBar.get());
    Ball* pB = static_cast<Ball*>(mBall.get());

    p->mVelocity = 0.0f;

    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        p->mVelocity = GameConstants::PLAYER_VELOCITY;
    }
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        p->mVelocity = -GameConstants::PLAYER_VELOCITY;
    }

    const float ENEMY_Y{ pE->GetPosY() }, BALL_Y{ pB->GetPosY()};

    if (pE->GetPosY() > pB->GetPosY()) { pE->mVelocity = GameConstants::ENEMY_VELOCITY; }
    else { pE->mVelocity = -GameConstants::ENEMY_VELOCITY; }

    p->Move();
    pE->Move(pB->GetPosY());
    pB->Move();
}
