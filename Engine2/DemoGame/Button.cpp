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
	AddListener(func);
}

Button::~Button()
{
}

void Button::Update(float deltaTime)
{
	__super::Update(deltaTime);
}

void Button::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
#ifdef _DEBUG
	D2DRenderer::GetInstance()->DrawAABB(*boundBox);
#endif
	//test->DrawFont(D2D1::ColorF(D2D1::ColorF::Black));
}

//그냥 멤버함수로 function을 들고있고.. 매개변수는 가능한가? 
void Button::OnClick() //각클래스가 재정의하기는 그렇고.. 
{
	if (clickFunc != nullptr)		
		clickFunc();
	std::cout << "Clicked"; //이거는 디버그 확인용
	//여기서 로직처리하기.. 
}
