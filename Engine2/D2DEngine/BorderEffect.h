#pragma once
#include "IEffect.h"
#include <wrl/client.h>

class BorderEffect : public IEffect
{
public:
	BorderEffect(ID2D1Bitmap* _Bitmap);
	virtual ~BorderEffect();
	virtual void EffectUpdate(float deltaTime);

	D2D1::ColorF color = { 0.0f, 0.0f, 0.0f, 0.0f };

	D2D1_MATRIX_5X4_F matrix = D2D1::Matrix5x4F(
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 100,
		0, 1, 0, 0);

	ID2D1Effect* colorMatrixEffect;
};

