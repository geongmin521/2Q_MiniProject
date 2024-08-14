#include "pch.h"
#include "GaussianBlurEffect.h"
#include "D2DRenderer.h"

GaussianBlurEffect::GaussianBlurEffect(ID2D1Bitmap* _Bitmap)
{
	D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1GaussianBlur, &DefaultEffect);
	DefaultEffect->SetInput(0, _Bitmap);
}

GaussianBlurEffect::~GaussianBlurEffect()
{
	if (DefaultEffect)
	{
		DefaultEffect->Release();
		DefaultEffect = nullptr;
	}
}

void GaussianBlurEffect::EffectUpdate(float deltaTime)
{
	DefaultEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, blurVal);
}
