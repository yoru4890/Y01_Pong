#include "Player.h"

Player::Player(D2DFramework* pFramework) : Actor(pFramework, L"Images/bar.png")
{
	mX = 924.0f - 66.0f;
	mY = (75.0f + 693.0f) / 2 -60.0f;

	mVelocity = 0.0f;
}

void Player::Draw()
{
	auto pRT = mpFramework->GetRenderTarget();
	if (!pRT)
	{
		return;
	}
	auto size = mpBitmap->GetPixelSize();

	auto matTranslate = D2D1::Matrix3x2F::Translation(mX, mY);
	pRT->SetTransform(matTranslate);

	D2D1_RECT_F rect{ 0,0,static_cast<float>(size.width), static_cast<float>(size.height) };
	pRT->DrawBitmap(mpBitmap, rect, mOpacity);

}

void Player::Move()
{
	auto ny = mY + UPVECTOR.y * mVelocity;

	if (ny >= 91.0f && ny <= 573.0f)
	{
		mY = ny;
	}
}
