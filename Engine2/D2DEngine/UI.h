#pragma once
#include "GameObject.h"

class AABB;
class UI : public GameObject //���� ������Ʈ�� ��ӹ�������.. ���� ó���ұ�? ���� ������ �и��ɰŰ��Ƽ�.. �ٵ� ��� �߸𸣰ڱ���.. 
{
public:
	UI();
	virtual ~UI() = default;
	void AddText(std::wstring text, int size);
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha =1) override;

};

