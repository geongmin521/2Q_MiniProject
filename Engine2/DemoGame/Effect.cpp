#include "pch.h"
#include "Bitmap.h"
#include "Animation.h"
#include "Transform.h"
#include "D2DRenderer.h"
#include "Pools.h"
#include "Effect.h"

Effect::Effect(int id, std::string imagepath, std::string csvpath,int renderOrder)
{
	this->id = id;
	AddComponent(new Animation(L"..\\Data\\Image\\Effect\\" + Utility::convertFromString(imagepath) + L".png", L"..\\Data\\CSV\\Effect\\" + Utility::convertFromString(csvpath) + L".csv"));
	GetComponent<Animation>()->SetAnimation(0, false, false);
	this->renderOrder = renderOrder;
}

Effect::~Effect()
{

}

void Effect::Init(MathHelper::Vector2F location,float _scale,bool loop)
{
//GetComponent<Bitmap>()->LoadD2DBitmap(L"..\\Data\\Image\\" + imagePath);
	transform->SetRelativeScale({ _scale,_scale });
	transform->SetRelativeLocation(location);
	if (GetComponent<Animation>() != nullptr)
	GetComponent<Animation>()->SetAnimation(0, false, loop);
}

void Effect::Update(float deltaTime)
{
	__super::Update(deltaTime);
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
