#include "../D2DEngine/pch.h"
#include "../D2DEngine/EventSystem.h"
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/Transform.h"
#include "Button.h"

Button::Button()
{
	AddComponent(new Bitmap(L"..\\Data\\Image\\Button_Start_Click.png")); 
	//transform->SetRelativeScale({ 0.1f,0.1f }); //아 이게 변경되면.. 월드에도 반영되게 한다고했지?
	SetBoundBox(0, 0, GetComponent<Bitmap>()->GetSize()); //바운드 박스의 크기도 따라갈수있도록만들고
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
}

//그냥 멤버함수로 function을 들고있고.. 매개변수는 가능한가? 
void Button::OnClick() //각클래스가 재정의하기는 그렇고.. 
{
	if (clickFunc != nullptr)		
		clickFunc();
	std::cout << "Clicked"; //이거는 디버그 확인용
	//여기서 로직처리하기.. 
}
