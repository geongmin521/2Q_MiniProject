#pragma once
#include "GameObject.h"
#include "IDamageNotify.h"
#include "IColliderNotify.h"

class Container;
class Map : public GameObject
{
private:
	Container* grid[4][4];
	int hp;
public:
	Map();
	~Map();
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha =1);

};

