#pragma once
#include "GameObject.h"
#include "IDamageNotify.h"

class Sculpture : public GameObject, public IDamageNotify
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
};

