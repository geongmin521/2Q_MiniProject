#pragma once
#include "GameObject.h"

class AABB;
class UI : public GameObject //게임 오브젝트도 상속받지말고.. 따로 처리할까? 뭔가 완전히 분리될거같아서.. 근데 사실 잘모르겠긴해.. 
{
public:
	UI();
	virtual ~UI() = default;
	void AddText(std::wstring text, int size);
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha =1) override;

};

