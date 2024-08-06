#include "../D2DEngine/pch.h"
#include "../D2DEngine/EventSystem.h"
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/Transform.h"
#include "Button.h"

Button::Button()
{
	AddComponent(new Bitmap(L"..\\Data\\Image\\Button_Start_Click.png")); 
	//transform->SetRelativeScale({ 0.1f,0.1f }); //�� �̰� ����Ǹ�.. ���忡�� �ݿ��ǰ� �Ѵٰ�����?
	SetBoundBox(0, 0, GetComponent<Bitmap>()->GetSize()); //�ٿ�� �ڽ��� ũ�⵵ ���󰥼��ֵ��ϸ����
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

//�׳� ����Լ��� function�� ����ְ�.. �Ű������� �����Ѱ�? 
void Button::OnClick() //��Ŭ������ �������ϱ�� �׷���.. 
{
	if (clickFunc != nullptr)		
		clickFunc();
	std::cout << "Clicked"; //�̰Ŵ� ����� Ȯ�ο�
	//���⼭ ����ó���ϱ�.. 
}
