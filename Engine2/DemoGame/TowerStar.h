#pragma once

//타워 성급을 나타내기 위한 비트맵출력 오브젝트
#include "../D2DEngine/GameObject.h"
class TowerStar : public GameObject
{
public:
	Bitmap* star;
	TowerStar();
	virtual ~TowerStar();
	GameObject* starOnwer;
	void SetStarOnwer(GameObject* obj) { starOnwer = obj;}
	void Init(GameObject* obj,int level); //init에 타워레벨 넣어줘서 비트맵구별;
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
};

