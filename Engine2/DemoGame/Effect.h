#pragma once
#include "GameObject.h"
class Effect : public GameObject
{

	float duration = 0; //이펙트 유지시간
	float elapsedTime = 0;
public:
	Effect(int id, std::string imagepath, std::string csvpath,bool isAni =true);
	virtual ~Effect();
	
	void Init(MathHelper::Vector2F location, float _scale,float _duration = 0);
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget, float Alpha = 1);
};




