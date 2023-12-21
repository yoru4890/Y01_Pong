#include "Player.h"
#include "Constants.h"

Player::Player(D2DFramework* pFramework) : Actor(pFramework, L"Images/bar.png"), mVelocity{0.0f}
{
	mX = GameConstants::BOTTOM_RIGHT_X - POS_X;
	mY = (GameConstants::TOP_LEFT_Y + GameConstants::BOTTOM_RIGHT_Y - SIZE_Y) / 2;
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

	if (ny >= GameConstants::TOP_LEFT_Y + GameConstants::WALL_THICK && ny <= GameConstants::BOTTOM_RIGHT_Y - SIZE_Y)
	{
		mY = ny;
	}
}

float Player::GetPosX()
{
	return mX;
}

float Player::GetPosY()
{
	return mY;
}
