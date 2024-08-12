#pragma once
#include "GameObject.h"

class TowerStar : public GameObject
{
public:
	TowerStar();
	virtual ~TowerStar();
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
};

