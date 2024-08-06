#pragma once
#include "../D2DEngine/UI.h"

class Shop: public UI //��Ŭ����? ��� �׳� UI������Ʈ���� �������� ������ �ʿ��� �Լ����� ������
{
private:
	bool isLock[5];
	int Id[5]; //���� ������ �� ������ ���̵�? 
	int reroll; //���� ���Ѱ���
	std::vector<GameObject*> subUi;
public:

	Shop();
	virtual ~Shop();
	void Reroll();
	void Spawn(); //���⼭ ���ս� ó���ϴ°͵� �������ϰ�.. 
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
};

