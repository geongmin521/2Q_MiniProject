#pragma once
#include "GameObject.h"

class TowerStar : public GameObject
{
public:
	TowerStar(int Level);
	virtual ~TowerStar();
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha =1);
};

