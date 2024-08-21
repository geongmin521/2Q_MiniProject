#include "pch.h"
#include "EventSystem.h"
#include "Bitmap.h"
#include "D2DRenderer.h"
#include "Transform.h"
#include "D2DFont.h"
#include "Button.h"
#include "Utility.h"

Button::Button(std::wstring imagePath, std::function<void(void)> func ,ButtonType type)
{
	renderOrder += 10;
	name = Utility::convertFromWString(imagePath);
	SetListener(func);
	std::wstring path;
	if (type == ButtonType::Blink)
	{
		path = L"../Data/Image/UI/Button/" + imagePath + L"_Nomal.png";
		Click = [this]() { Blick(); };
	}
	else if (type == ButtonType::Active)
	{
		path = L"../Data/Image/UI/Button/" + imagePath + L"_Enable.png";
		Click = [this]() { Active(); };
	}
	else if (type == ButtonType::Single)
	{
		path = L"../Data/Image/UI/Button/" + imagePath + L".png";
		Click = [this]() { Single(); };
	}

	AddComponent(new Bitmap(path));
	SetBoundBox(0, 0, GetComponent<Bitmap>()->GetSize());
}

Button::~Button()
{
}

void Button::Update(float deltaTime)
{
	__super::Update(deltaTime);
	if (isClicked == true)
	{
		Timer += deltaTime;
		Click();
	}
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

void Button::OnClick() //생성도안됬는데 들어오는건가? 
{
	if (clickFunc != nullptr && interactive == true && isClicked == false) //아 이벤트를 보내고 람다식하고 나면 본인은 지워졌으니까.. 이게 문제구나. 
		clickFunc();
	std::cout << "Clicked"; 
	isClicked = true;
	Timer = 0;
}

void Button::Blick()
{
	std::wstring path;
	if (aniTime / 3 >= Timer)
	{
		path = L"../Data/Image/UI/Button/" + Utility::convertFromString(name) + L"_Click.png";
	}
	else if (aniTime / 2 >= Timer) //0.1초후 이미지 바꾸기 
	{
		path = L"../Data/Image/UI/Button/" + Utility::convertFromString(name) + L"_Over.png";
	}
	else if (aniTime >= Timer) //0.2초후 다시 정상으로 돌리기
	{
		Timer = 0;
		isClicked = false;
		path = L"../Data/Image/UI/Button/" + Utility::convertFromString(name) + L"_Nomal.png";
	}
	GetComponent<Bitmap>()->LoadD2DBitmap(path);
}

void Button::Single()
{
	Timer = 0;
	isClicked = false;
}

void Button::Active() //락같은경우는 그냥 바뀐걸로 이미지를 들고있고.. 배속은 .blink하고 끝나면 최종형태를 저장하고있음
{
	isEnable = !isEnable;
	SetIsEnable(isEnable);
	Timer = 0;
	isClicked = false;
}

void Button::SetIsEnable(bool enable)
{
	isEnable = enable;
	std::wstring path;
		path = L"../Data/Image/UI/Button/" + Utility::convertFromString(name);
	if (isEnable == true)
		path += L"_Enable.png";
	else
		path += L"_Disable.png";
	GetComponent<Bitmap>()->LoadD2DBitmap(path);
}
