#pragma once
#include "GameObject.h"
class Effect : public GameObject
{
public:
	Effect(int id, std::string imagepath, std::string csvpath,int renderorder = 102);
	virtual ~Effect();
	
	void Init(MathHelper::Vector2F location, float _scale,float _duration = 0);
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget, float Alpha = 1);
};




