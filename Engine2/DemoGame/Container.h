#pragma once
#include "UI.h"
#include "IDropAble.h"
#include "IClickAble.h"
class MoveIcon;
class Container: public UI ,public IDropAble, IClickAble//��ģ���� UI�� �����? dropAble �������̽��� ��ӹ����ű���
{
private:
public:
	bool isContain;
	Container();
	virtual ~Container();
	void Clear(); // ����������� ���� ������
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha =1) override; //���⿡ �ϴ� �ڽ��� �׷�����?
	virtual void OnDrop(GameObject* ui) override; //�µ�ӿ��� ���� �巡�� ���� UI�� ���;���
	virtual void OnClick() override;
};

//���°� �����ܻ��·� �ٽ� ���ư��°� �³�? �װ� �ƴ϶�� �� ����ҰŰ�����.. Ÿ���� UI�� �ƴ϶�..