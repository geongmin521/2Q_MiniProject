#include "pch.h"
#include "Bitmap.h"
#include "Animation.h"
#include "Transform.h"
#include "D2DRenderer.h"
#include "Pools.h"
#include "Effect.h"

Effect::Effect(int id, std::string imagepath, std::string csvpath, bool isAni)
{
	this->id = id;
	//Add를 멀 받아서 멀기준으로 만들어주지
	if (isAni == true)
	{
		AddComponent(new Animation(L"..\\Data\\Image\\Tower\\" + Utility::convertFromString(imagepath) + L".png", L"..\\Data\\CSV\\TowerAni\\" + Utility::convertFromString(csvpath) + L".csv"));
		GetComponent<Animation>()->SetAnimation(0, false, false);
	}
	else
	{
		AddComponent(new Bitmap(L"..\\Data\\Image\\Light.png"));
	}
	renderOrder = 102;
}

Effect::~Effect()
{

}

void Effect::Init(MathHelper::Vector2F location,float _scale,float _duration)
{
	//AddComponent(new Bitmap(L"..\\Data\\Image\\" + imagePath);
	//GetComponent<Bitmap>()->LoadD2DBitmap(L"..\\Data\\Image\\" + imagePath);
	transform->SetRelativeScale({ _scale,_scale });
	transform->SetRelativeLocation(location);
	if (GetComponent<Bitmap>() != nullptr)
	{
		duration = _duration;
		elapsedTime = 0;
	}
	if (GetComponent<Animation>() != nullptr)
	GetComponent<Animation>()->SetAnimation(0, false, false);
}

void Effect::Update(float deltaTime)
{
	__super::Update(deltaTime);

	if (GetComponent<Bitmap>() != nullptr) //비트맵만있을땐 시간지나면 지워지게끔

	{
		elapsedTime += deltaTime;
		if (elapsedTime >= duration)
		{
			Pools::GetInstance()->AddPool(this);
		}
	}

	if (GetComponent<Animation>() != nullptr)  //비트맵만 점점사라지는 이펙트가 있을수있으니까
	{
		if (GetComponent<Animation>()->IsEnd())
			Pools::GetInstance()->AddPool(this);
	}

	
}

void Effect::Render(ID2D1HwndRenderTarget* pRenderTarget, float Alpha)
{
	__super::Render(pRenderTarget);
}
