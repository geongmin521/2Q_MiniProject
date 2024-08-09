#pragma once
#include "../D2DEngine/GameObject.h"

class Container;
class Map : public GameObject
{
private:
	//맵에경우는 변경가능성이적고 고정되니까 이차원배열로하자
	Container* grid[4][4];
public:
	Map();
	~Map();
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
};

