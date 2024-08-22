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
	bool isFrame = false;
	std::string tag;
	HPBar(float& curHp, float maxHp,std::string tag,bool isFrame = false);
	virtual ~HPBar();
	virtual void Init(float maxHp);
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha =1);
};


