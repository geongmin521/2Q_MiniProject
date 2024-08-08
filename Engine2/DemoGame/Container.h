#pragma once
#include "../D2DEngine/UI.h"
#include "../D2DEngine/IDropAble.h"
class MoveIcon;
class Container: public UI ,public IDropAble//��ģ���� UI�� �����? dropAble �������̽��� ��ӹ����ű���
{
private:
	MoveIcon* containUi;
	
public:
	Container();
	virtual ~Container();
	void Clear(); // ����������� ���� ������
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override; //���⿡ �ϴ� �ڽ��� �׷�����?
	virtual void OnDrop(UI* ui) override; //�µ�ӿ��� ���� �巡�� ���� UI�� ���;���
};

//���°� �����ܻ��·� �ٽ� ���ư��°� �³�? �װ� �ƴ϶�� �� ����ҰŰ�����.. Ÿ���� UI�� �ƴ϶�..