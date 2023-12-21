#include "Ball.h"
#include "Constants.h"
#include <random>
#include <cmath>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> distribution(1,2);

Ball::Ball(D2DFramework* pFramework) : Actor(pFramework, L"Images/ball.png"), mVelocity{ INITIAL_VELOCITY }, isGoal{ false }, scorePlayer{}, scoreEnemy{}
{
	mX = (GameConstants::BOTTOM_RIGHT_X + GameConstants::TOP_LEFT_X + GameConstants::WALL_THICK) / 2;
	mY = (GameConstants::BOTTOM_RIGHT_Y + GameConstants::TOP_LEFT_Y + GameConstants::WALL_THICK) / 2;
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

void Ball::Move(float playerX, float playerY, float enemyX, float enemyY)
{
	auto nx{ mX + moveVector.x * mVelocity };
	auto ny{ mY + moveVector.y * mVelocity };

	if (nx >= GameConstants::TOP_LEFT_X + GameConstants::WALL_THICK && nx <= GameConstants::BOTTOM_RIGHT_X - SIZE_X)
	{
		if (playerY <= ny + SIZE_Y && playerY + GameConstants::BAR_SIZE_HEIGHT >= ny)
		{
			if (nx + SIZE_X >= playerX)
			{
				moveVector.x *= -1;
				mVelocity += VELOCITY_INCREMENT;
				nx = playerX - SIZE_X;
			}
		}

		if (enemyY <= ny + SIZE_Y && enemyY + GameConstants::BAR_SIZE_HEIGHT >= ny)
		{
			if (nx <= enemyX + GameConstants::BAR_SIZE_WIDTH)
			{
				moveVector.x *= -1;
				mVelocity += VELOCITY_INCREMENT;
				nx = enemyX + GameConstants::BAR_SIZE_WIDTH;
			}
		}

		mX = nx;
	}
	else
	{
		isGoal = true;
		if (nx < (GameConstants::BOTTOM_RIGHT_X + GameConstants::TOP_LEFT_X + GameConstants::WALL_THICK) / 2)
		{
			scorePlayer++;
		}
		else
		{
			scoreEnemy++;
		}
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

void Ball::CheckGoal()
{
	if (isGoal)
	{
		mX = (GameConstants::BOTTOM_RIGHT_X + GameConstants::TOP_LEFT_X + GameConstants::WALL_THICK) / 2;
		mY = (GameConstants::BOTTOM_RIGHT_Y + GameConstants::TOP_LEFT_Y + GameConstants::WALL_THICK) / 2;
		mVelocity = INITIAL_VELOCITY;
		
		float ranX{ static_cast<float>(distribution(gen)) - 1.5f };
		float ranY{ static_cast<float>(distribution(gen)) - 1.5f };

		moveVector.x = ranX;
		moveVector.y = ranY;
		isGoal = false;
	}
}

float Ball::GetPosY()
{
	return mY + SIZE_Y / 2;
}

int Ball::GetScorePlayer()
{
	return scorePlayer;
}

int Ball::GetScoreEnemy()
{
	return scoreEnemy;
}
