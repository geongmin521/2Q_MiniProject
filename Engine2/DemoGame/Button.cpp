#include "../D2DEngine/pch.h"
#include "../D2DEngine/EventSystem.h"
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/D2DFont.h"
#include "Button.h"

Button::Button(std::wstring imagePath)
{
	AddComponent(new Bitmap(imagePath));
	SetBoundBox(0, 0, GetComponent<Bitmap>()->GetSize());
	//test = new D2DFont;
	//test->LoadFont(L"Cooper");
	//D2DFont().CreateLayoutText();
	//test->CreateLayoutText(L"gdgdg");
	//test->Sort(Setting::MIDDLE);
	//test->SetFontLocation(Setting::MIDDLE);
	//test->CreateLayoutText(L"aaaa");
	//test->SetSize(200, { 0, 4 });//텍스트를 변경해야하는데. 정렬도 초기화가 안되야하고. 
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
