#pragma once
#include "../D2DEngine/UI.h"

class GameOver :public UI
{
private:
	std::vector<GameObject*> subUi;
public:
	GameOver();
	~GameOver();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
};

