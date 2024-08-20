#pragma once
#include "IEffect.h"

class MorphologyEffect : public  IEffect
{
public:
	MorphologyEffect(ID2D1Bitmap* _Bitmap);
	virtual ~MorphologyEffect();
	virtual void EffectUpdate(float deltaTime);

	int val = 0;

	bool test;
	float testSpeed = 1;
};

