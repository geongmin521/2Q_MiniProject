#include "pch.h"
#include "MorphologyEffect.h"
#include "D2DRenderer.h"

MorphologyEffect::MorphologyEffect(ID2D1Bitmap* _Bitmap)
{
	D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1Morphology, &DefaultEffect);
	DefaultEffect->SetInput(0, _Bitmap);
	
}

MorphologyEffect::~MorphologyEffect()
{
	if (DefaultEffect)
	{
		DefaultEffect->Release();
		DefaultEffect = nullptr;
	}
}

void MorphologyEffect::EffectUpdate(float deltaTime)
{
	DefaultEffect->SetValue(D2D1_MORPHOLOGY_PROP_MODE, D2D1_MORPHOLOGY_MODE_ERODE);
    DefaultEffect->SetValue(D2D1_MORPHOLOGY_PROP_WIDTH, val);
}
