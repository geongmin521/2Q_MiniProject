#include "pch.h"
#include "Bitmap.h"
#include "Animation.h"
#include "Transform.h"
#include "D2DRenderer.h"
#include "Pools.h"
#include "Effect.h"

Effect::Effect(int id)
{
	renderOrder = 106;
	std::wstring effect = idtoString(static_cast<EffectId>(id));
	this->id = id;
	AddComponent(new Animation(L"..\\Data\\Image\\Effect\\" + effect + L"Effect.png", L"..\\Data\\CSV\\Effect\\" + effect + L".csv"));
	if(!(effect.find(L"Summon") == std::wstring::npos))
		renderOrder = 93;
	GetComponent<Animation>()->SetAnimation(0, false, false);
}

Effect::~Effect()
{

}

void Effect::Init(MathHelper::Vector2F location,float _scale,bool loop)
{
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
