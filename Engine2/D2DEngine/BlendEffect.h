#pragma once
#include "IEffect.h"

class BlendEffect : public IEffect
{
public:
	BlendEffect(ID2D1Bitmap* _Bitmap, ID2D1Bitmap* _BitmapTwo);
	virtual ~BlendEffect();
	virtual void EffectUpdate(float deltaTime);

};

