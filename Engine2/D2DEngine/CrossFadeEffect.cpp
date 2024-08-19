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
        weight += fadeSpeed * deltaTime; // ���̵� �� �� weight ����
        if (weight > 1.0f)
        {
            weight = 1.0f; // weight ���� 1�� ���� �ʵ��� ����
        }
    }
    else
    {
        weight -= fadeSpeed * deltaTime; // ���̵� �ƿ� �� weight ����
        if (weight < 0.0f)
        {
            weight = 0.0f; // weight ���� 0���� ���� �ʵ��� ����
        }
    }

	DefaultEffect->SetValue(D2D1_CROSSFADE_PROP_WEIGHT, weight);
}
