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
	Transform* LightTransform; // 이거 꼭 트랜스폼으로 할 필요가 있을까 고민 사항??

	float LightX = 0; // 트렌스폼 없이
	float LightY = 0;
	void SetLightPos(float _x, float _y) { LightX = _x; LightY = _y; }
};

