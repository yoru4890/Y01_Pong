#include "PlayerScores.h"
#include "Constants.h"

PlayerScores::PlayerScores(D2DFramework* pFramework) : Actor(pFramework, L"Images/scores.png"), scorePlayer{}
{
}

void PlayerScores::Draw()
{
	auto pRT = mpFramework->GetRenderTarget();
	if (!pRT)
	{
		return;
	}
	auto size = mpBitmap->GetPixelSize();
	float num{ (scorePlayer % 10) * static_cast<float>(size.width) / 10 };

	auto matTranslate = D2D1::Matrix3x2F::Translation(PX, PY);
	pRT->SetTransform(matTranslate);

	D2D1_RECT_F sourceRect{ num, 0, num + SIZE, static_cast<float>(size.height) };
	D2D1_RECT_F destinationRect{ 0, 0, SIZE, static_cast<float>(size.height) };

	pRT->DrawBitmap(mpBitmap, destinationRect, mOpacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sourceRect);
	
}

void PlayerScores::SetScore(int score)
{
	scorePlayer = score;
}
