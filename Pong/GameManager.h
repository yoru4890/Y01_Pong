#pragma once
#include <vector>
#include <memory>
#include "D2DFramework.h"
#include "Actor.h"

class GameManager : public D2DFramework
{
private:
	std::vector<std::shared_ptr<Actor>> mWalls;
	std::vector<std::shared_ptr<Actor>> mPlayerScore;
	std::vector<std::shared_ptr<Actor>> mEnemyScore;
	std::shared_ptr<Actor> mPlayerBar;
	std::shared_ptr<Actor> mEnemyBar;
	std::shared_ptr<Actor> mBall;

public:
	virtual HRESULT Initialize(HINSTANCE hInstance, LPCWSTR title = L"Pong", UINT width = 1024, UINT height = 768) override;
	virtual void Render() override;
	virtual void Release() override;

	void CheckInput();

};

