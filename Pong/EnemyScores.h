#pragma once
#include "Actor.h"
class EnemyScores : public Actor
{
private:
	const float EX{ 378.0f };
	const float EY{ 120.0f };
	const float SIZE{ 64.0f };

	int scoreEnemy{};

public:
	explicit EnemyScores(D2DFramework* pFramework);

	virtual void Draw() override;

	void SetScore(int score);
};

