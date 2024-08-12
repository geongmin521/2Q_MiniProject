#pragma once
#include "UI.h"

class Victory :public UI
{
private:
	std::vector<GameObject*> subUi;
public:
	Victory();
	~Victory();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha =1) override;
};

