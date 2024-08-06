#include "../D2DEngine/pch.h"
#include "Factory.h"
#include "ShowWave.h"

ShowWave::ShowWave()
{
	float LeftPadding = 800;
	Fac->CreateImage(L"BigBack.png", { WinHalfSizeX ,WinHalfSizeY }, { 2,2 }, &sprites);
	for (int i = 0; i < 4; i++)
	{
		Fac->CreateImage(L"vampire.png", { LeftPadding + i * 130 ,WinHalfSizeY }, { 1,1 }, &sprites);
		//�ؽ�Ʈ�� �߰��ϱ�...
	}
		
	Fac->CreateButton(L"smallBack.png", [this]() { isActive = false; }, { WinHalfSizeX + 400, WinHalfSizeY - 400 }, &exitButton);
	
	for (auto var : sprites)
		var->isActive = false;
	//�˾��� ���� �� �ִ� ��ư

}

ShowWave::~ShowWave()
{
	//�������� ���ݱ��� ���� ��� ui�� ���������.. 
}

void ShowWave::Show()
{
	isActive = true;
	sprites[0]->isActive = true;//ù��°�� ����̶� ��������������
	for (auto var : sprites) //�̰͵� �����ε������� �����ҰŸ� �׳� for������ ó���ص��ǰ�
		var->isActive = true;
	//

	//�̰Ŵ� ������ ������ csv���� �����ؾ��ϴϱ� ���̵� ������.. 
	//������ �Ŵ������� �ҷ����� ���̺�ҷ�����... 
}

void ShowWave::Update(float deltaTime)
{
	//�̰� �׳� ������Ʈ�������̶� ������Ʈ���� ������Ʈ�� �������ָ�ɵ�
	for (auto var : sprites)
		var->Update(deltaTime);
	exitButton[0]->Update(deltaTime);
}

void ShowWave::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	for (auto var : sprites)
		var->Render(pRenderTarget);
	exitButton[0]->Render(pRenderTarget); //����ϳ��ۿ����µ� ���丮�� �ִ±��������� ���Ͱ��Ǿ����.. 
}