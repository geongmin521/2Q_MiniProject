#pragma once
#include "GameObject.h"

class AABB;
class UI : public GameObject //���� ������Ʈ�� ��ӹ�������.. ���� ó���ұ�? ���� ������ �и��ɰŰ��Ƽ�.. �ٵ� ��� �߸𸣰ڱ���.. 
{
public: //init�ϼ����ֱ��ѵ�.. �������ذ�����.. ������Ʈ Ǯ���� �������� �ڵ����� ���� ȣ��ɼ��հ� 
	UI();
	virtual ~UI() = default;
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha =1) override;

};

