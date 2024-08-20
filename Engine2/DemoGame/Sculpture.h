#pragma once
#include "GameObject.h"
#include "IDamageNotify.h"
#include "IClickAble.h"
#include "IOnMouse.h"

class Sculpture : public GameObject, public IDamageNotify, public IClickAble,public IOnMouse
{
private:
	float hp;
	
public:
	Sculpture();
	~Sculpture();
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget, float Alpha = 1);
	virtual void Hit(float damage, float knockback = 0) override;
	virtual void Heal(float heal) override; 
	virtual void OnClick() override;
	virtual void OnMouse() override;
	virtual void OutMouse() override;
};

