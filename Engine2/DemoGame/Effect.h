#pragma once
#include "GameObject.h"
class Effect : public GameObject
{

	float duration = 0; //이펙트 유지시간
	float elapsedTime = 0;
public:
	Effect();
	Effect(MathHelper::Vector2F location,float _duration);
	virtual ~Effect();
	
	void Init(std::wstring imagePath, MathHelper::Vector2F location, float _duration); //init에서 각 비트맵 애니메이션 생성했다가 지워야하나?
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget, float Alpha = 1);
};

