#include "../D2DEngine/pch.h"
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/D2DRenderer.h"
#include "TowerBase.h"
#include "EnemyBase.h"
#include "HPBar.h"

HPBar::HPBar()
{
	hpBar = new Bitmap(L"..\\Data\\Image\\hpbar.png");
	AddComponent(hpBar); //
	renderOrder = 101;
	//transform->SetRelativeScale({ 0.2f,0.2f });
}

HPBar::~HPBar()
{
}

void HPBar::Init(GameObject* obj)
{
	SetHPOnwer(obj);
	//transform->SetParent(HPOwner->transform);
	transform->SetRelativeLocation({ 500, 200});
	isActive = true;

}


void HPBar::Update(float deltaTime)
{
	if (HPOwner->isActive == false)
	{
		isActive = false;
	}
	float scaleX = (HPOwner->perHP / 100.f);  // 체력 퍼센트
	float origin = hpBar->GetSize().x;         // 원래 크기
	float newOrigin = origin * scaleX;
	float move = std::abs((origin - newOrigin) / 1.5f);
	
	float pre = GetWorldLocation().x;
	__super::Update(deltaTime);



	// 1. 스케일 조정 (중앙 기준)
	transform->SetRelativeScale({ scaleX , 0.65 });


	// 2. 왼쪽 기준으로 위치 보정
	
	//transform->SetRelativeLocation({  - move, GetWorldLocation().y });
}

void HPBar::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}
