#pragma once
#include "Actor.h"
class Ball : public Actor
{
private:
	D2D_POINT_2F moveVector{ 0.5f, -0.5f };
	const float INITIAL_VELOCITY{ 2.0f };
	const float VELOCITY_INCREMENT{ 0.5f };
	const float SIZE_X{ 24.0f };
	const float SIZE_Y{ 24.0f };
	bool isGoal{};
	float mVelocity{};

	int scorePlayer{};
	int scoreEnemy{};

public:
	explicit Ball(D2DFramework* pFramework);

	virtual void Draw() override;

	void Move(float playerX, float playerY, float enemyX, float enemyY);

	void CheckGoal();

	float GetPosY();

	int GetScorePlayer();
	int GetScoreEnemy();
};

