#include "pch.h"
#include "FadeOut.h"
#include "GameObject.h"
#include "D2DRenderer.h"
#include "transform.h"
#include "World.h"
#include "Bitmap.h"

FadeOut::FadeOut(std::function<void(void)> func,bool isFade)
{
	if(isFade)
		alpha = 0;
	else
		alpha = 1;
	AddComponent(new Bitmap(L"../Data/Image/FadeOut.png"));
	transform->SetRelativeLocation(WinHalfSizeXY);
	renderOrder = 3000;
	isfade = isFade;
	
	this->func = func;
}

FadeOut::~FadeOut()
{
}

void FadeOut::Update(float deltaTime)
{
	__super::Update(deltaTime);
	
	alpha += deltaTime / duration;


	if(isfade)
	{
		alpha += deltaTime / duration;
		if (alpha > 1.0f)
		{
			SetActive(false);
			func();
			owner->DeleteGameObject(this);
			
		}
	}
	else
	{
		alpha -= deltaTime / duration;

		if (alpha < 0)
		{
			SetActive(false);
			func();
			//owner->DeleteGameObject(this);
		}
	}
}

void FadeOut::Render(ID2D1HwndRenderTarget* pRenderTarget, float Alpha)
{
	__super::Render(pRenderTarget, alpha);
}

