#include "../D2DEngine/pch.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/Animation.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/Music.h"



#include "Arrow.h"

Arrow::Arrow()
{
	SetBoundBox(0, 0, 40, 36);
	AddComponent(new Animation(L"..\\Data\\Image\\ken.png", L"Arrow"));
	AddComponent(new Movement(transform));
	//AddComponent(new BoxCollider(boundBox, CollisionType::Overlap, this, CollisionLayer::Bullet));
	
	renderOrder = 100;
}

Arrow::~Arrow()
{
}

void Arrow::Init(MathHelper::Vector2F velocity, MathHelper::Vector2F location)
{
	velocity = velocity * speed;
	GetComponent<Movement>()->SetVelocity(velocity);
	transform->SetRelativeLocation({ location.x + 50.0f,location.y - 20.f });
}

void Arrow::Inits(GameObject* target, MathHelper::Vector2F location)
{
	this->target = target;
	transform->SetRelativeLocation({ location.x + 50.0f,location.y - 20.f });
}

void Arrow::Update(float deltaTime)
{
	__super::Update(deltaTime);
	if (target->isActive == true)
	{
		MathHelper::Vector2F dir = MathHelper::Vector2F(target->GetWorldLocation()) - MathHelper::Vector2F(GetWorldLocation());
		dir.Normalize();
		GetComponent<Movement>()->SetVelocity(dir * speed);
	}
	else
	{
		isActive = false;
	}
	if (std::abs(target->GetWorldLocation().x - GetWorldLocation().x) <= 1.0f||    //일단 타겟크기를 몰라서 1.0으로헀는대 타겟의 몸통 크기? 로하면 될듯함 isActive가 꺼질때 공격판정넣기?
		std::abs(target->GetWorldLocation().y - GetWorldLocation().y) <= 1.0f)
		isActive = false;
	
}

void Arrow::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}

