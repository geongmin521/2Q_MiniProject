#include "pch.h"
#include "Bitmap.h"
#include "Transform.h"
#include "TowerStar.h"


TowerStar::TowerStar()
{
	AddComponent(new Bitmap(L"..\\Data\\Image\\1Star.png")); 
	renderOrder = 101;
	transform->SetRelativeScale({ 0.05f,0.05f });
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
