#include "EnemyScores.h"

EnemyScores::EnemyScores(D2DFramework* pFramework) : Actor(pFramework, L"Images/scores.png"), scoreEnemy{}
{
}

void EnemyScores::Draw()
{
	auto pRT = mpFramework->GetRenderTarget();
	if (!pRT)
	{
		return;
	}
	auto size = mpBitmap->GetPixelSize();
	float num{ (scoreEnemy % 10) * static_cast<float>(size.width) / 10 };

	auto matTranslate = D2D1::Matrix3x2F::Translation(EX, EY);
	pRT->SetTransform(matTranslate);

	D2D1_RECT_F sourceRect{ num, 0, num + SIZE, static_cast<float>(size.height) };
	D2D1_RECT_F destinationRect{ 0, 0, SIZE, static_cast<float>(size.height) };

	pRT->DrawBitmap(mpBitmap, destinationRect, mOpacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sourceRect);
}

void EnemyScores::SetScore(int score)
{
	scoreEnemy = score;
}
