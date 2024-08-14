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
	float scaleX = (curHp / maxHp);  // 체력 퍼센트
	float origin = hpBar->bitmap->GetSize().width;     // 원래 크기
	float newOrigin = origin * scaleX;
	float move = (origin - newOrigin) / 2.0f;

	// 1. 스케일 조정 (중앙 기준)
	transform->SetRelativeScale({ scaleX * 0.5f, 0.35 }); //0.5곱하는건 전체크기조절을 위해 크기에맞게 수정
	// 2. 왼쪽 기준으로 위치 보정
	transform->SetRelativeLocation({ - move * 0.5f,70.f });
}

void HPBar::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
	__super::Render(pRenderTarget);
}
