#include "../D2DEngine/pch.h"
#include "Combination.h"
#include "Factory.h"

Combination::Combination()
{
	//나가기 버튼
	Fac->CreateButton(L"smallBack.png", [this]() {isActive = false; }, { WinHalfSizeX + 500, WinHalfSizeY - 400 }, &subUi);
	//조합표 이미지 하나로?
	Fac->CreateImage(L"Combination.png", { WinHalfSizeX , WinHalfSizeY  }, { 1,1 }, &subUi);
	renderOrder = 100;
}

Combination::~Combination()
{
}

void Combination::Update(float deltaTime)
{
	for (auto var : subUi)
		var->Update(deltaTime);
}

void Combination::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	for (auto var : subUi)
		var->Render(pRenderTarget);
}
