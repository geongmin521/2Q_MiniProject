#pragma once
#include "IEffect.h"
class Transform;
class PointSpecularEffect : public IEffect
{
public:
	PointSpecularEffect(ID2D1Bitmap* _Bitmap, Transform* _Transform);
	PointSpecularEffect(ID2D1Bitmap* _Bitmap, float _Transformx, float _Transformy);
	virtual ~PointSpecularEffect();
	virtual void EffectUpdate(float deltaTime);

	float LightZonter = 10.0f;
	Transform* LightTransform; // �̰� �� Ʈ���������� �� �ʿ䰡 ������ ��� ����??

	float LightX = 0; // Ʈ������ ����
	float LightY = 0;
	void SetLightPos(float _x, float _y) { LightX = _x; LightY = _y; }
};

