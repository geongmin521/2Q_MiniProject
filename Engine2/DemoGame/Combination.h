#pragma once
#include "UI.h"

class Combination :public UI
{
private:
	std::vector<GameObject*> subUi; //������.. �ֵ鵵��� ������ ����ѵ�? �߻�ȭ�� ������ �׷���?
public:
	Combination();
	~Combination();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
};
