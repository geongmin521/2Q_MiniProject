#include "pch.h"
#include "Sculpture.h"
#include "CircleCollider.h"
#include "Circle.h"
#include "Transform.h"
#include "Bitmap.h"
#include "Effect.h"
#include "Pools.h"
#include "GameManager.h"

Sculpture::Sculpture() //얘가 iclickable을 상속받을까?
{
	name = "Tower";
	AddComponent(new CircleCollider(boundBox, new Circle(transform->GetWorldLocation(), 500.0f), CollisionType::Overlap, nullptr, CollisionLayer::Tower)); //이렇게 보내면될까? //그냥 박스로해버릴까? 
	AddComponent(new Bitmap(L"../Data/Image/1Star.png")); //이렇게 보내면될까? 
	GetComponent<CircleCollider>()->SetOffset({ -300,0 });
	hp = 100; //위쪽으로 지나가는 애들이 따라와야할텐데... 
	Effect* effect = dynamic_cast<Effect*>(Pools::GetInstance().get()->PopPool(2006));
	effect->Init({ GetWorldLocation().x +100 ,GetWorldLocation().y + 300}, 1.3f,true); //이펙트 생성
}

Sculpture::~Sculpture()
{
}

void Sculpture::Update(float deltaTime)
{
	__super::Update(deltaTime);
}

void Sculpture::Render(ID2D1HwndRenderTarget* pRenderTarget, float Alpha)
{
	__super::Render(pRenderTarget);
}

void Sculpture::Hit(float damage, float knockback)
{
	hp -= damage;
	if (hp <= 0)
	{
		GameManager::GetInstance().get()->events[Event::GameOverEvent]();
	}
}

void Sculpture::Heal(float heal)
{
}
