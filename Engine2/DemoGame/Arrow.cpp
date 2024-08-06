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
	AddComponent(new BoxCollider(boundBox, CollisionType::Overlap, this, CollisionLayer::Bullet));
	
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

void Arrow::Update(float deltaTime)
{
	__super::Update(deltaTime);
	
	
}

void Arrow::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}

void Arrow::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{
	
}

void Arrow::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{
	if (otherComponent->owner->name == "Enemy")
	{
		this->isActive = false; //지우진않고 끄기만
		std::cout << "적 충돌" << std::endl;
	}
}

void Arrow::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{

}

void Arrow::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}
