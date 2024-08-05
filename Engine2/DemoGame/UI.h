#pragma once
#include "../D2DEngine/GameObject.h"

class UI : public GameObject //UI도 게임 오브젝트의 일종이지만.. UI 이벤트 시스템을 통해서.. 마우스 이벤트를 입력받는걸로하자.. //그리고 특히 UI는 계층 구조를 더 잘따름
{
public:
	UI();
	~UI();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
};

