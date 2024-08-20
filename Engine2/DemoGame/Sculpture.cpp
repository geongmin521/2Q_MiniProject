#include "pch.h"
#include "Sculpture.h"
#include "CircleCollider.h"
#include "Circle.h"
#include "Transform.h"
#include "Bitmap.h"
#include "Effect.h"
#include "Pools.h"
#include "GameManager.h"
#include "Factory.h"
#include "EventSystem.h"

Sculpture::Sculpture() //얘가 iclickable을 상속받을까?
{
	name = "Tower"; 
	SetBoundBox(0,0, 150,150);
	AddComponent(new CircleCollider(boundBox, new Circle(transform->GetWorldLocation(), 500.0f), CollisionType::Overlap, nullptr, CollisionLayer::Tower)); 
	AddComponent(new Bitmap(L"../Data/Image/Statue_Nomal.png"));
	GetComponent<CircleCollider>()->SetOffset({ -300,0 });
	eventSystem->Ui.insert(this);
	hp = 100; 
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

void Sculpture::OnClick()
{
	if(gameManager->isBattle ==false)
		gameManager->events[Event::OpenGodStore]();
}

void Sculpture::OnMouse()
{
	GetComponent<Bitmap>()->LoadD2DBitmap(L"../Data/Image/Statue_OnMouse.png");
}

void Sculpture::OutMouse()
{
	GetComponent<Bitmap>()->LoadD2DBitmap(L"../Data/Image/Statue_Nomal.png");
}
