#include "Ball.h"

Ball::Ball(D2DFramework* pFramework) : Actor(pFramework, L"Images/ball.png")
{
	mX = 500.0f;
	mY = 372.0f;

	mVelocity = 1.0f;
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

	if (nx >= 116.0f && nx <= 900.0f)
	{
		mX = nx;
	}
	else
	{
		moveVector.x *= -1;
		mVelocity++;
	}

	if (ny >= 91.0f && ny <= 669.0f)
	{
		mY = ny;
	}
	else
	{
		moveVector.y *= -1;
		mVelocity++;
	}
}
