#pragma once
#include "IEffect.h"
class ColorMatrixEffect : public IEffect
{
public:
	ColorMatrixEffect(ID2D1Bitmap* _Bitmap);
	virtual ~ColorMatrixEffect();
	virtual void EffectUpdate(float deltaTime);

	D2D1_MATRIX_5X4_F ColorMatrix;
};

