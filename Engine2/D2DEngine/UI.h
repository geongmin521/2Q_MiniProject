#pragma once
#include "GameObject.h"

class AABB;
class UI : public GameObject //���� ������Ʈ�� ��ӹ�������.. ���� ó���ұ�? ���� ������ �и��ɰŰ��Ƽ�.. �ٵ� ��� �߸𸣰ڱ���.. 
{
public:
	UI();
	virtual ~UI();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;

};

