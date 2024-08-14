#pragma once
#include "IEffect.h"

class GaussianBlurEffect : public IEffect
{
public:
	GaussianBlurEffect(ID2D1Bitmap* _Bitmap);
	virtual ~GaussianBlurEffect();
	virtual void EffectUpdate(float deltaTime);

	float blurVal = 0;
};

