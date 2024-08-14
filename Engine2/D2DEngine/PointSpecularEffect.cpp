#include "pch.h"
#include "PointSpecularEffect.h"
#include "D2DRenderer.h"
#include "Transform.h"

PointSpecularEffect::PointSpecularEffect(ID2D1Bitmap* _Bitmap, Transform* _Transform)
{
	D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1PointSpecular, &DefaultEffect);
	LightTransform = _Transform;

	// ǥ���� ������ ���� (���� ���� ��� �ؼ����� �����մϴ�)
	FLOAT surfaceScale = 1.0f;
	DefaultEffect->SetValue(D2D1_POINTSPECULAR_PROP_SURFACE_SCALE, surfaceScale);

	// ����ŧ�� ��� ���� (���� ������ �����մϴ�)
	FLOAT specularConstant = 2.0f;
	DefaultEffect->SetValue(D2D1_POINTSPECULAR_PROP_SPECULAR_CONSTANT, specularConstant);

	// ����ŧ�� ���� ���� (���� �ݻ� ������ �����մϴ�, ���� ���ϼ��� ���� ��ī�Ӱ� �ݻ�˴ϴ�)
	FLOAT specularExponent = 50.0f;
	DefaultEffect->SetValue(D2D1_POINTSPECULAR_PROP_SPECULAR_EXPONENT, specularExponent);

	// ���� ���� ���� (�¾�ó�� �ణ�� ������� ��� �����մϴ�)
	D2D1_COLOR_F lightColor = D2D1::ColorF(1.0f, 0.9f, 0.7f);
	DefaultEffect->SetValue(D2D1_POINTSPECULAR_PROP_COLOR, lightColor);

	// Ŀ�� ���� ���� ���� (ȿ���� ���� ������ �����մϴ�)
	D2D1_VECTOR_2F kernelUnitLength = D2D1::Vector2F(1.0f, 1.0f);
	DefaultEffect->SetValue(D2D1_POINTSPECULAR_PROP_KERNEL_UNIT_LENGTH, kernelUnitLength);

	// ������ ��� ���� (��ǰ���� �����Ͽ� �� �ε巴�� ǥ��)
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
