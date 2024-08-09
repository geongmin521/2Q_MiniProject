#pragma once
#include "../D2DEngine/GameObject.h"
class Bitmap;
class HPBar : public GameObject
{
public:
	Bitmap* hpBar;
	HPBar();
	virtual ~HPBar();
	GameObject* HPOwner;
	void SetHPOnwer(GameObject* obj) { HPOwner = obj; }
	void Init(GameObject* obj);
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
};


