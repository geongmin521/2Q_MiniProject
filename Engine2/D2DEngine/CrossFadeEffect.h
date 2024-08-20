#pragma once
#include "IEffect.h"

class CrossFadeEffect : public IEffect
{
public:
	CrossFadeEffect(ID2D1Bitmap* _Bitmap, ID2D1Bitmap* _Bitmap2);
	virtual ~CrossFadeEffect();
	virtual void EffectUpdate(float deltaTime);

	float weight = 0.0;
	bool isFadeIn = true;
	float fadeSpeed = 0.5f;
};

