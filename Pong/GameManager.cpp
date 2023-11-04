#include "GameManager.h"

HRESULT GameManager::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height)
{
    HRESULT hr;
    hr = D2DFramework::Initialize(hInstance, title, width, height);
    ThrowIfFailed(hr, "Failed in D2DFramework::Initailize()");

    // 파일 읽기
    for (float x = 100, y = 75; x <= 924; x++) { mWalls.push_back(std::make_shared<Actor>(this, L"Images/wall.png", x, y)); }
    for (float x = 100, y = 75; y <= 693; y++) { mWalls.push_back(std::make_shared<Actor>(this, L"Images/wall.png", x, y)); }
    for (float x = 924, y = 75; y <= 693; y++) { mWalls.push_back(std::make_shared<Actor>(this, L"Images/wall.png", x, y)); }
    for (float x = 100, y = 693; x <= 924; x++) { mWalls.push_back(std::make_shared<Actor>(this, L"Images/wall.png", x, y)); }
    for (float x = 512, y = 75; y <= 687; y += 33) { mWalls.push_back(std::make_shared<Actor>(this, L"Images/wall.png", x, y)); }

    return S_OK;
}

void GameManager::Render()
{
    mspRenderTarget->BeginDraw();
    mspRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
    mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));

    for (auto& wall : mWalls)
    {
        wall->Draw();
    }

    HRESULT hr = mspRenderTarget->EndDraw();

    if (hr == D2DERR_RECREATE_TARGET)
    {
        CreateDeviceResources();
    }
}

void GameManager::Release()
{
    mWalls.clear();

    D2DFramework::Release();
}
