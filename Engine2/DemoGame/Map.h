#pragma once
#include "../D2DEngine/GameObject.h"

class Container;
class Map : public GameObject
{
private:
	//�ʿ����� ���氡�ɼ������� �����Ǵϱ� �������迭������
	Container* grid[4][4];
public:
	Map();
	~Map();
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
};

