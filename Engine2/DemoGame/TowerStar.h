#pragma once

//Ÿ�� ������ ��Ÿ���� ���� ��Ʈ����� ������Ʈ
#include "../D2DEngine/GameObject.h"
class TowerStar : public GameObject
{
public:
	Bitmap* star;
	TowerStar();
	virtual ~TowerStar();
	GameObject* starOnwer;
	void SetStarOnwer(GameObject* obj) { starOnwer = obj;}
	void Init(GameObject* obj,int level); //init�� Ÿ������ �־��༭ ��Ʈ�ʱ���;
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
};

