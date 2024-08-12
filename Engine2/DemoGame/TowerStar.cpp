#include "pch.h"
#include "Bitmap.h"
#include "Transform.h"
#include "D2DRenderer.h"
#include "TowerStar.h"


TowerStar::TowerStar()
{
	AddComponent(new Bitmap(L"..\\Data\\Image\\1Star.png")); 
	renderOrder = 101;
	transform->SetRelativeScale({ 0.2f,0.2f });
}

TowerStar::~TowerStar()
{
}

void TowerStar::Update(float deltaTime)
{
	__super::Update(deltaTime);
}

void TowerStar::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}
