#include "pch.h"
#include "ColorMatrixEffect.h"
#include "D2DRenderer.h"

ColorMatrixEffect::ColorMatrixEffect(ID2D1Bitmap* _Bitmap)
{
	D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &DefaultEffect);
	DefaultEffect->SetInput(0, _Bitmap);
}

ColorMatrixEffect::~ColorMatrixEffect()
{
	if (DefaultEffect)
	{
		DefaultEffect->Release();
		DefaultEffect = nullptr;
	}
}

void ColorMatrixEffect::EffectUpdate(float deltaTime)
{
	DefaultEffect->SetValue(D2D1_COLORMATRIX_PROP_COLOR_MATRIX, ColorMatrix);
}
