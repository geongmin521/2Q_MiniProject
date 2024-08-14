#pragma once
#include "IEffect.h"
class Transform;
class PointSpecularEffect : public IEffect
{
public:
	PointSpecularEffect(ID2D1Bitmap* _Bitmap, Transform* _Transform);
	virtual ~PointSpecularEffect();
	virtual void EffectUpdate(float deltaTime);

	float LightZonter = 10.0f;
	Transform* LightTransform; // �̰� �� Ʈ���������� �� �ʿ䰡 ������ ��� ����??
};

