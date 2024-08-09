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
	float scaleX = (HPOwner->perHP / 100.f);  // ü�� �ۼ�Ʈ
	float origin = hpBar->GetSize().x;         // ���� ũ��
	float newOrigin = origin * scaleX;
	float move = std::abs((origin - newOrigin) / 1.5f);
	
	float pre = GetWorldLocation().x;
	__super::Update(deltaTime);



	// 1. ������ ���� (�߾� ����)
	transform->SetRelativeScale({ scaleX , 0.65 });


	// 2. ���� �������� ��ġ ����
	
	//transform->SetRelativeLocation({  - move, GetWorldLocation().y });
}

void HPBar::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}
