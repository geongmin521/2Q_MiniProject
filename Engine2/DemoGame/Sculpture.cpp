#include "pch.h"
#include "Sculpture.h"
#include "CircleCollider.h"
#include "Circle.h"
#include "Transform.h"
#include "Bitmap.h"
#include "GameManager.h"

Sculpture::Sculpture() //�갡 iclickable�� ��ӹ�����?
{
	name = "Tower";
	AddComponent(new CircleCollider(boundBox, new Circle(transform->GetWorldLocation(), 500.0f), CollisionType::Overlap, nullptr, CollisionLayer::Tower)); //�̷��� ������ɱ�? //�׳� �ڽ����ع�����? 
	AddComponent(new Bitmap(L"../Data/Image/1Star.png")); //�̷��� ������ɱ�? 
	GetComponent<CircleCollider>()->SetOffset({ -300,0 });
	hp = 100; //�������� �������� �ֵ��� ����;����ٵ�... 
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
