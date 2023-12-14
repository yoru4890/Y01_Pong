#include "Ball.h"
#include "Constants.h"

Ball::Ball(D2DFramework* pFramework) : Actor(pFramework, L"Images/ball.png"), mVelocity{INITIAL_VELOCITY}
{
	mX = (GameConstants::BOTTOM_RIGHT_X - GameConstants::TOP_LEFT_X) / 2;
	mY = (GameConstants::BOTTOM_RIGHT_Y - GameConstants::TOP_LEFT_Y) / 2;
}

void Ball::Draw()
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

void Ball::Move()
{
	auto nx = mX + moveVector.x * mVelocity;
	auto ny = mY + moveVector.y * mVelocity;

	if (nx >= GameConstants::TOP_LEFT_X + GameConstants::WALL_THICK && nx <= GameConstants::BOTTOM_RIGHT_X - SIZE_X)
	{
		mX = nx;
	}
	else
	{
		moveVector.x *= -1;
		mVelocity += VELOCITY_INCREMENT;
	}

	if (ny >= GameConstants::TOP_LEFT_Y + GameConstants::WALL_THICK && ny <= GameConstants::BOTTOM_RIGHT_Y - SIZE_Y)
	{
		mY = ny;
	}
	else
	{
		moveVector.y *= -1;
		mVelocity += VELOCITY_INCREMENT;
	}
}
