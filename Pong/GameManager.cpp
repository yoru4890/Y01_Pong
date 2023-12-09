#include "GameManager.h"
#include "Player.h"
#include "Ball.h"

HRESULT GameManager::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height)
{
    HRESULT hr;
    hr = D2DFramework::Initialize(hInstance, title, width, height);
    ThrowIfFailed(hr, "Failed in D2DFramework::Initailize()");
    
    const D2D_POINT_2F WALL_TOP_LEFT { 100.0f, 75.0f };
    const D2D_POINT_2F WALL_BOTTOM_RIGHT { 924.0f, 693.0f };

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

    for (float y = WALL_TOP_LEFT.y; y <= WALL_BOTTOM_RIGHT.y; y += 32.55f)
    {
        mWalls.push_back(std::make_shared<Actor>(this, L"Images/wall.png", (WALL_TOP_LEFT.x + WALL_BOTTOM_RIGHT.x)/2, y));
    }

    mPlayerBar = std::make_shared<Player>(this);

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
    mPlayerBar.reset();
    mWalls.clear();

    D2DFramework::Release();
}

void GameManager::CheckInput()
{
    Player* p = static_cast<Player*>(mPlayerBar.get());
    Ball* pB = static_cast<Ball*>(mBall.get());

    p->mVelocity = 0.0f;

    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        p->mVelocity = 4.0f;
    }
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        p->mVelocity = -4.0f;
    }

    p->Move();
    pB->Move();
}
