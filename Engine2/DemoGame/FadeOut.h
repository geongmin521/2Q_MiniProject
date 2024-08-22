#pragma once
#include "GameObject.h"
class Image;
class FadeOut : public GameObject
{

public:
	FadeOut(std::function<void(void)> func,bool isFade = true);
	virtual ~FadeOut();
	bool isfade;
	std::function<void(void)> func;
	bool isfun = false;
	float alpha = 0;
	float duration = 4.0f;
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget, float Alpha = 1) override;
};

