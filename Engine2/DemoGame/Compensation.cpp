#include "../D2DEngine/pch.h"
#include "Compensation.h"
#include "Factory.h"

Compensation::Compensation() 
{
	float LeftPadding = 200;
	for (int i = 0; i < 3; i++)//보상 버튼 //눌리면 아마 선택된 상태로 전환되고 
		Fac->CreateButton(L"ImageBack.png", [i, this]() {  }, { LeftPadding + i * 200, WinHalfSizeY + 100 }, &subUi);
	//한번더 누르면 보상확정
	Fac->CreateButton(L"ImageBack.png", [this]() {  }, { LeftPadding + 500, WinHalfSizeY + 300 }, &subUi);
}

Compensation::~Compensation()
{
}

void Compensation::Update(float deltaTime)
{
	for (auto var : subUi)
		var->Update(deltaTime);
}

void Compensation::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	for (auto var : subUi)
		var->Render(pRenderTarget);
}
