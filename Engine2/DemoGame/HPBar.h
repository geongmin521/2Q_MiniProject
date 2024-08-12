#pragma once
#include "GameObject.h"
class Bitmap;
class HPBar : public GameObject
{
private:
	float& curHp;
	float maxHp;
public:
	Bitmap* hpBar;
	HPBar(float& curHp, float maxHp);
	virtual ~HPBar();
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
};


