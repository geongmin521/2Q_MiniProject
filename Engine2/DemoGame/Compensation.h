#pragma once
#include "../D2DEngine/UI.h"

class Compensation :public UI
{
private:
	std::vector<GameObject*> subUi; //������.. �ֵ鵵��� ������ ����ѵ�? �߻�ȭ�� ������ �׷���?
public:
	Compensation();
	~Compensation();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
};
