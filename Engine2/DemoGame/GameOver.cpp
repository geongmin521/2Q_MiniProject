#include "../D2DEngine/pch.h"
#include "Factory.h"
#include "GameOver.h"

GameOver::GameOver()
{
	Fac->CreateImage(L"BigBack.png", WinHalfSizeXY, { 2,2 }, &subUi);

	Fac->CreateButton(L"ImageBack.png", [this]() {}, { WinHalfSizeX, WinHalfSizeY + 100 }, &subUi);//�ٽý���
	//��� ó���ұ�.. ���� �ٽ� �ε��ϸ�ɵ�?
	Fac->CreateButton(L"ImageBack.png", [this]() {}, { WinHalfSizeX, WinHalfSizeY + 300 }, &subUi);//��������
	//�������� ���� ��ȯ�ϸ�ǰ�.. 
}

//���Ŵ����� ���� ���Ű�.. 
//�ŷε��ϸ� ������� �����ϰ� ���ο� ���� ����⸸�ϸ��.. 

GameOver::~GameOver()
{
}

void GameOver::Update(float deltaTime)
{
}

void GameOver::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
}
