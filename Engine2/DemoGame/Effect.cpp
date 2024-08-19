#include "pch.h"
#include "Bitmap.h"
#include "Animation.h"
#include "Transform.h"
#include "D2DRenderer.h"
#include "Pools.h"
#include "Effect.h"

Effect::Effect()
{
	AddComponent(new Bitmap(L"..\\Data\\Image\\Light.png")); //이펙트를 종류별로 다 다른객체로 만들어둬야하나 prefab처럼 //아니면 그림바꿔치기?
	renderOrder = 90;
}

Effect::Effect(MathHelper::Vector2F location, float _duration)
{
	this->transform->SetRelativeLocation(location);
	this->duration = _duration;
}

Effect::~Effect()
{

}

void Effect::Init(std::wstring imagePath, MathHelper::Vector2F location, float _duration)
{
	transform->SetRelativeLocation(location);
	duration = _duration;
	//AddComponent(new Bitmap(L"..\\Data\\Image\\" + imagePath);
	GetComponent<Bitmap>()->LoadD2DBitmap(L"..\\Data\\Image\\" + imagePath);
	elapsedTime = 0;   
}

void Effect::Update(float deltaTime)
{
	__super::Update(deltaTime);
	elapsedTime += deltaTime;
	if (elapsedTime >= duration)
	{
		SetActive(false);           
	}
}

void Effect::Render(ID2D1HwndRenderTarget* pRenderTarget, float Alpha)
{
	__super::Render(pRenderTarget);
}
