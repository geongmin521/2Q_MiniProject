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
	transform->SetParent(HPOwner->transform);
	transform->SetRelativeLocation({ 0, 70.f });
	isActive = true;

}

void HPBar::Update(float deltaTime)
{
	if (HPOwner->isActive == false)
	{
		isActive = false;
	}
	
	__super::Update(deltaTime);

	float scaleX = (HPOwner->perHP / 100.f);  // ü�� �ۼ�Ʈ
	float origin = GetWorldLocation().x;         // ���� ũ��
	float newOrigin = origin * scaleX;
	float move = (origin - newOrigin) / 4;
	transform->SetRelativeLocation({ -move, 70.f });

	// 1. ������ ���� (�߾� ����)
	transform->SetRelativeScale({ scaleX , 0.65 });


	// 2. ���� �������� ��ġ ����
	std::cout << scaleX << std::endl;
}

void HPBar::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}
