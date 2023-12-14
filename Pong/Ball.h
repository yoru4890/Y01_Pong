#pragma once
#include "Actor.h"
class Ball : public Actor
{
private:
	D2D_POINT_2F moveVector{ 1.0f, -1.0f };
	const float INITIAL_VELOCITY{ 1.0f };
	const float VELOCITY_INCREMENT{ 1.0f };
	const float SIZE_X{ 24.0f };
	const float SIZE_Y{ 24.0f };

public:
	float mVelocity;

public:
	explicit Ball(D2DFramework* pFramework);

	virtual void Draw() override;

	void Move();
};

