#pragma once
#include "../D2DEngine/UI.h"

class Compensation :public UI
{
private:
	std::vector<GameObject*> subUi; //나머지.. 애들도모두 구조가 비슷한뎨? 추상화로 묶을걸 그랬나?
public:
	Compensation();
	~Compensation();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
};
