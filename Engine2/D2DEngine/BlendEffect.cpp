#include "pch.h"
#include "BlendEffect.h"
#include "D2DRenderer.h"

BlendEffect::BlendEffect(ID2D1Bitmap* _Bitmap, ID2D1Bitmap* _BitmapTwo)
{
	D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1Blend, &DefaultEffect);
	DefaultEffect->SetInput(0, _Bitmap);
	DefaultEffect->SetInput(1, _BitmapTwo);
	DefaultEffect->SetValue(D2D1_BLEND_PROP_MODE, D2D1_BLEND_MODE_LINEAR_LIGHT);
}

BlendEffect::~BlendEffect()
{
	if (DefaultEffect)
	{
		DefaultEffect->Release();
		DefaultEffect = nullptr;
	}
}

void BlendEffect::EffectUpdate(float deltaTime)
{

}
