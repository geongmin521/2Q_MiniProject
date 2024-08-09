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
	//test->SetSize(200, { 0, 4 });//�ؽ�Ʈ�� �����ؾ��ϴµ�. ���ĵ� �ʱ�ȭ�� �ȵǾ��ϰ�. 
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

//�׳� ����Լ��� function�� ����ְ�.. �Ű������� �����Ѱ�? 
void Button::OnClick() //��Ŭ������ �������ϱ�� �׷���.. 
{
	if (clickFunc != nullptr)		
		clickFunc();
	std::cout << "Clicked"; //�̰Ŵ� ����� Ȯ�ο�
	//���⼭ ����ó���ϱ�.. 
}
