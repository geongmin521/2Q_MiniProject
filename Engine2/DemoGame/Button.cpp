#include "pch.h"
#include "EventSystem.h"
#include "Bitmap.h"
#include "D2DRenderer.h"
#include "Transform.h"
#include "D2DFont.h"
#include "Button.h"

Button::Button(std::wstring imagePath, std::function<void(void)> func)
{
	AddComponent(new Bitmap(L"../Data/Image/" + imagePath));
	SetBoundBox(0, 0, GetComponent<Bitmap>()->GetSize());
	SetListener(func);
}

Button::~Button()
{
}

void Button::Update(float deltaTime)
{
	__super::Update(deltaTime);
}

void Button::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
	float alpah = (interactive == true) ? 1 : 0.5f;
	__super::Render(pRenderTarget, alpah);
#ifdef _DEBUG
	D2DRenderer::GetInstance()->DrawAABB(*boundBox);
#endif
	//test->DrawFont(D2D1::ColorF(D2D1::ColorF::Black));
}

void Button::OnClick() 
{
	if (clickFunc != nullptr && interactive == true)
		clickFunc();
	std::cout << "Clicked"; 
}
