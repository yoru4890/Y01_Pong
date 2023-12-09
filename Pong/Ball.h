#pragma once
#include "Actor.h"
class Ball : public Actor
{
private:
	D2D_POINT_2F moveVector{ 1.0f, -1.0f };

public:
	float mVelocity;

public:
	explicit Ball(D2DFramework* pFramework);

	virtual void Draw() override;

	void Move();
};

