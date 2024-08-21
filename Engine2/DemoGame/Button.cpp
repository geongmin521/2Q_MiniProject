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

void Button::OnClick() //�������ȉ�µ� �����°ǰ�? 
{
	if (clickFunc != nullptr && interactive == true && isClicked == false) //�� �̺�Ʈ�� ������ ���ٽ��ϰ� ���� ������ ���������ϱ�.. �̰� ��������. 
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
	else if (aniTime / 2 >= Timer) //0.1���� �̹��� �ٲٱ� 
	{
		path = L"../Data/Image/UI/Button/" + Utility::convertFromString(name) + L"_Over.png";
	}
	else if (aniTime >= Timer) //0.2���� �ٽ� �������� ������
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

void Button::Active() //���������� �׳� �ٲ�ɷ� �̹����� ����ְ�.. ����� .blink�ϰ� ������ �������¸� �����ϰ�����
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
