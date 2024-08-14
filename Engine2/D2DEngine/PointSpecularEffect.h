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
	Transform* LightTransform; // 이거 꼭 트랜스폼으로 할 필요가 있을까 고민 사항??
};

