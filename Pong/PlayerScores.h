#pragma once
#include "Actor.h"
class PlayerScores : public Actor
{
private:
	const float PX{584.0f};
	const float PY{120.0f};
	const float SIZE{ 64.0f };

	int scorePlayer{};

public:
	explicit PlayerScores(D2DFramework* pFramework);

	virtual void Draw() override;

	void SetScore(int score);
};

