#include "../D2DEngine/pch.h"
#include "Compensation.h"
#include "Factory.h"

Compensation::Compensation() 
{
	float LeftPadding = 200;
	for (int i = 0; i < 3; i++)//���� ��ư //������ �Ƹ� ���õ� ���·� ��ȯ�ǰ� 
		Fac->CreateButton(L"ImageBack.png", [i, this]() {  }, { LeftPadding + i * 200, WinHalfSizeY + 100 }, &subUi);
	//�ѹ��� ������ ����Ȯ��
	Fac->CreateButton(L"ImageBack.png", [this]() {  }, { LeftPadding + 500, WinHalfSizeY + 300 }, &subUi);
}

Compensation::~Compensation()
{
}

void Compensation::Update(float deltaTime)
{
	for (auto var : subUi)
		var->Update(deltaTime);
}

void Compensation::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	for (auto var : subUi)
		var->Render(pRenderTarget);
}
