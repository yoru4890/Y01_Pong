#pragma once
#include "Actor.h"
class Enemy :public Actor
{
private:
	const D2D_POINT_2F UPVECTOR{ 0.0f, -1.0f };
	const float POS_X{ 66.0f };
	const float SIZE_X{ 24.0f };
	const float SIZE_Y{ 120.0f };
public:
	float mVelocity;

public:
	explicit Enemy(D2DFramework* pFramework);

	virtual void Draw() override;

	void Move();

	float GetPosY();
};

