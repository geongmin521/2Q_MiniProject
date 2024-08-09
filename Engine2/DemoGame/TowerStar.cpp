#include "../D2DEngine/pch.h"
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/D2DRenderer.h"
#include "TowerStar.h"


TowerStar::TowerStar()
{
	star = new Bitmap(L"..\\Data\\Image\\1Star.png");
	AddComponent(star); //
	renderOrder = 101;
	transform->SetRelativeScale({ 0.2f,0.2f });
}

TowerStar::~TowerStar()
{
}

void TowerStar::Init(GameObject* obj,int level)
{
	SetStarOnwer(obj);
	transform->SetParent(starOnwer->transform);
	transform->SetRelativeLocation({ 0, -70.f });
	isActive = true;
	switch (level) {
	case 1:
		star->LoadD2DBitmap(L"..\\Data\\Image\\1Star.png"); 
		break;
	case 2:
		star->LoadD2DBitmap(L"..\\Data\\Image\\2Star.png");
		break;
	default:
		star->LoadD2DBitmap(L"..\\Data\\Image\\1Star.png"); 
	}
	
}

void TowerStar::Update(float deltaTime)
{
	if (starOnwer->isActive == false)
	{
		isActive = false;
	}
	__super::Update(deltaTime);
	
}

void TowerStar::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}
