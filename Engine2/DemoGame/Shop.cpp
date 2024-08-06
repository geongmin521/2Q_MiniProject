#include "../D2DEngine/pch.h"
#include "Factory.h"
#include "Shop.h"

Shop::Shop() //��.. ���.. ������ �����ݵ�.. �ٵ� �ϰ����� ��� �����ϱ⵵ ����.. �̷��� ���ó���ؾ��ϳ�...
//�Ű������� ���� ������.. �ƴѰ�? bool Ÿ�� ��ſ� .. �������ִ� ���͸� �ѱ��?  �װ� ���� �����Ű�����.. 
{
	Fac->CreateImage(L"BigBack.png", WinHalfSizeXY, {2,2}, &subUi);
	float LeftPadding = 700; //���ʿ� �󸶸�ŭ�� ������ ����
	for (int i = 0; i < 5; i++)//������
		Fac->CreateImage(L"arrow.png", { LeftPadding + i * 130 ,WinHalfSizeY }, {1,1}, &subUi);
	for (int i = 0; i < 5; i++)//���� ��ױ�
		Fac->CreateButton(L"ImageBack.png", [i, this]() { isLock[i] = !isLock[i]; }, { LeftPadding + i * 130, WinHalfSizeY + 100 },&subUi);
	//��������� ���ٽĿ��� ������ this�� ĸ���س����ϴ±���.. 

	Fac->CreateButton(L"ImageBack.png", std::bind(&Shop::Reroll, this), { LeftPadding + 250, WinHalfSizeY + 100 }, &subUi);
	//����ǥ�� ���� ������ ���� ����ϴ� �ؽ�Ʈ�ڽ�.. 
	Fac->CreateImage(L"ImageBack.png", { LeftPadding + 250, WinHalfSizeY + 200 }, { 1,1 }, &subUi);
	//���Ѱ����� Ƚ���� ����ϴ� �ؽ�Ʈ�ڽ�
	Fac->CreateImage(L"ImageBack.png", { LeftPadding + 250, WinHalfSizeY + 300 }, { 1,1 }, &subUi);
	//����ǥ Ȯ�� ��ư //���带 ���ؼ� ������Ʈ�� �����ü�������.. �׷� ����ǥ ��ü ����.. �׳� ������ �̹����� �ξ� ���ҰŰ�����.. 
	//����ǥ�� �׳� ����̹����� ������? 
	Fac->CreateButton(L"ImageBack.png", std::bind(&Shop::Reroll, this), { LeftPadding + 450, WinHalfSizeY + 300 }, &subUi);
	//��ȯ�ϱ� ��ư
	Fac->CreateButton(L"ImageBack.png", std::bind(&Shop::Spawn, this), { LeftPadding + 450, WinHalfSizeY + 400 }, &subUi);
	//�� ��������� �� function�� ��°Ŵ� ���� �ٸ�����.. 
}//�װǾȵǰ�.. 
//�θ������Ʈ�� ���� ó���� ����ϰ� �ҷ��� ��� �ؾ��ұ�.. 

Shop::~Shop() //�α����� ������� �ؽ�ƮŬ������ �������� �ؽ�Ʈ �ڽ��� ������ ��������.. Ư������ ����Ҽ��ְ� ���ø����� �������������? 
{
}

void Shop::Reroll()
{
}
//�̷��� ��� able �̺�Ʈ�� �߻��Ҽ��� �־���ϰ� .. �ʵ� �������ϰ� ���Ƴ� �׳�.. ��.. 
void Shop::Spawn() //���� �κ��丮�� ����־���ϰ�.. �����̳� Ŭ������ �����ؾ��ϰ�.. 
{
}

void Shop::Update(float deltaTime)
{
	//�̰� �׳� ������Ʈ�������̶� ������Ʈ���� ������Ʈ�� �������ָ�ɵ�
	for (auto var : subUi)
		var->Update(deltaTime);
}

void Shop::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	for (auto var : subUi)
		var->Render(pRenderTarget);
}

//������ ���������� ���Ѵܰ踸 �θ�ɰŰ���.. ���忡 ������Ʈ�� ���� �ִ°� �ƴ϶�
//���⼭ ó���ϴ°ɷΰ���.. 

//Ʋ�� ���� ���� 