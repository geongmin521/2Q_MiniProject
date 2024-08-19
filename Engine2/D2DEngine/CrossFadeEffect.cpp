#include "pch.h"
#include "CrossFadeEffect.h"
#include "D2DRenderer.h"

CrossFadeEffect::CrossFadeEffect(ID2D1Bitmap* _Bitmap, ID2D1Bitmap* _Bitmap2)
{
	D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1CrossFade, &DefaultEffect);
	DefaultEffect->SetInput(0, _Bitmap);
	DefaultEffect->SetInput(1, _Bitmap2);

	weight = 0.0f; 
	isFadeIn = true;
}

CrossFadeEffect::~CrossFadeEffect()
{
	if (DefaultEffect)
	{
		DefaultEffect->Release();
		DefaultEffect = nullptr;
	}
}

void CrossFadeEffect::EffectUpdate(float deltaTime)
{
    if (isFadeIn)
    {
        weight += fadeSpeed * deltaTime; // 페이드 인 시 weight 증가
        if (weight > 1.0f)
        {
            weight = 1.0f; // weight 값이 1을 넘지 않도록 제한
        }
    }
    else
    {
        weight -= fadeSpeed * deltaTime; // 페이드 아웃 시 weight 감소
        if (weight < 0.0f)
        {
            weight = 0.0f; // weight 값이 0보다 작지 않도록 제한
        }
    }

	DefaultEffect->SetValue(D2D1_CROSSFADE_PROP_WEIGHT, weight);
}
