#include "pch.h"
#include "Bitmap.h"
#include "Transform.h"
#include "TowerStar.h"


TowerStar::TowerStar(int Level)
{
	switch (Level)
	{
	case 1:
		AddComponent(new Bitmap(L"..\\Data\\Image\\UI\\TowerUI\\star1.png"));
		break;
	case 2:
		AddComponent(new Bitmap(L"..\\Data\\Image\\UI\\TowerUI\\star2.png"));
		break;
	default:
		AddComponent(new Bitmap(L"..\\Data\\Image\\UI\\TowerUI\\star3.png"));
		break;
	}
	renderOrder = 101;
}

TowerStar::~TowerStar()
{
}

void TowerStar::Update(float deltaTime)
{
	__super::Update(deltaTime);
}

void TowerStar::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
	__super::Render(pRenderTarget);
}
