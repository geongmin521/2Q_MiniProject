#include "pch.h"
#include "PointSpecularEffect.h"
#include "D2DRenderer.h"
#include "Transform.h"

PointSpecularEffect::PointSpecularEffect(ID2D1Bitmap* _Bitmap, Transform* _Transform)
{
	D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1PointSpecular, &DefaultEffect);
	LightTransform = _Transform;

	// 표면의 스케일 설정 (높이 맵을 어떻게 해석할지 결정합니다)
	FLOAT surfaceScale = 1.0f;
	DefaultEffect->SetValue(D2D1_POINTSPECULAR_PROP_SURFACE_SCALE, surfaceScale);

	// 스펙큘러 상수 설정 (빛의 강도를 결정합니다)
	FLOAT specularConstant = 2.0f;
	DefaultEffect->SetValue(D2D1_POINTSPECULAR_PROP_SPECULAR_CONSTANT, specularConstant);

	// 스펙큘러 지수 설정 (빛의 반사 정도를 결정합니다, 높은 값일수록 빛이 날카롭게 반사됩니다)
	FLOAT specularExponent = 50.0f;
	DefaultEffect->SetValue(D2D1_POINTSPECULAR_PROP_SPECULAR_EXPONENT, specularExponent);

	// 빛의 색상 설정 (태양처럼 약간의 노란색을 띄게 설정합니다)
	D2D1_COLOR_F lightColor = D2D1::ColorF(1.0f, 0.9f, 0.7f);
	DefaultEffect->SetValue(D2D1_POINTSPECULAR_PROP_COLOR, lightColor);

	// 커널 단위 길이 설정 (효과의 세부 사항을 조절합니다)
	D2D1_VECTOR_2F kernelUnitLength = D2D1::Vector2F(1.0f, 1.0f);
	DefaultEffect->SetValue(D2D1_POINTSPECULAR_PROP_KERNEL_UNIT_LENGTH, kernelUnitLength);

	// 스케일 모드 설정 (고품질로 설정하여 더 부드럽게 표현)
	D2D1_POINTSPECULAR_SCALE_MODE scaleMode = D2D1_POINTSPECULAR_SCALE_MODE_LINEAR;
	DefaultEffect->SetValue(D2D1_POINTSPECULAR_PROP_SCALE_MODE, scaleMode);

	DefaultEffect->SetInput(0, _Bitmap);
}

PointSpecularEffect::~PointSpecularEffect()
{

}

void PointSpecularEffect::EffectUpdate(float deltaTime)
{
	D2D1_VECTOR_3F lightPosition = D2D1::Vector3F(LightTransform->GetWorldLocation().x, LightTransform->GetWorldLocation().y, LightZonter);
	DefaultEffect->SetValue(D2D1_POINTSPECULAR_PROP_LIGHT_POSITION, lightPosition);

	D2D1_VECTOR_3F pointsAt = D2D1::Vector3F(LightTransform->GetWorldLocation().x, LightTransform->GetWorldLocation().y, 0.0f);
	DefaultEffect->SetValue(D2D1_SPOTSPECULAR_PROP_POINTS_AT, pointsAt);
}
