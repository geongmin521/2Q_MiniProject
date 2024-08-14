#include "pch.h"
#include "Bitmap.h"
#include "Transform.h"
#include "HPBar.h"

HPBar::HPBar(float& curHp, float maxHp) : curHp(curHp) , maxHp(maxHp)
{
	hpBar = new Bitmap(L"..\\Data\\Image\\hpbar.png");
	AddComponent(hpBar); 
	renderOrder = 101;
}

HPBar::~HPBar()
{
}

void HPBar::Update(float deltaTime) 
{
	__super::Update(deltaTime);
	float scaleX = (curHp / maxHp);  // ü�� �ۼ�Ʈ
	float origin = hpBar->bitmap->GetSize().width;     // ���� ũ��
	float newOrigin = origin * scaleX;
	float move = (origin - newOrigin) / 2.0f;

	// 1. ������ ���� (�߾� ����)
	transform->SetRelativeScale({ scaleX * 0.5f, 0.35 }); //0.5���ϴ°� ��üũ�������� ���� ũ�⿡�°� ����
	// 2. ���� �������� ��ġ ����
	transform->SetRelativeLocation({ - move * 0.5f,70.f });
}

void HPBar::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
	__super::Render(pRenderTarget);
}
