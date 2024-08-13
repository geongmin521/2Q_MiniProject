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
	float alpah = (interactive == true) ? 1 : 0.5f; //바활성화시 반투명하게 그리기
	__super::Render(pRenderTarget, alpah);
#ifdef _DEBUG
	D2DRenderer::GetInstance()->DrawAABB(*boundBox);
#endif
	//test->DrawFont(D2D1::ColorF(D2D1::ColorF::Black));
}

//그냥 멤버함수로 function을 들고있고.. 매개변수는 가능한가? 
void Button::OnClick() //각클래스가 재정의하기는 그렇고.. 
{
	if (clickFunc != nullptr && interactive == true)//여기에 상호작용가능한지 만들어서 처리해놓고.. 만약 상호작용이 불가능하면 렌더를 좀 투명하게 만들어볼까? 오케이 이렇게하면되겟네.. 
		clickFunc();
	std::cout << "Clicked"; //이거는 디버그 확인용
	//여기서 로직처리하기.. 
}
