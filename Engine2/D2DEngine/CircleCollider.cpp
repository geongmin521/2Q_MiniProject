#include "pch.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "AABB.h"
#include "Circle.h"
#include "D2DRenderer.h"
#include "GameObject.h"
#include "Transform.h"

CircleCollider::CircleCollider(AABB* aabb, Circle* circle, CollisionType type, IColliderNotify* notify, CollisionLayer layer) : aabb(aabb), circle(circle)
{
	colliderType = ColliderType::Circle;
	collisionType = type; //아래 부분은 겹치니까 부모생성자에서 처리해도 될듯? 
	this->layer = layer;
	this->notify = notify;
}

CircleCollider::~CircleCollider()
{
}

bool CircleCollider::IsCollide(Collider* otherComponent)
{
	//상대가 서클일때랑, 박스일때  이 두경우 뿐임 //박스끼리 비교 서클끼리 비교.. 
	if (otherComponent->GetColliderType() == ColliderType::Box)
	{
		return  aabb->CheckIntersect(*((BoxCollider*)otherComponent)->aabb);
	}
	else
	{
		return  circle->CheckIntersect(*((CircleCollider*)otherComponent)->circle);
	}
}

void CircleCollider::Update(float deltaTime)
{
	if (owner->transform)
		aabb->Center = owner->transform->GetWorldLocation(); //이부분은 각 콜라이더로 이전한다
}

void CircleCollider::Render(ID2D1RenderTarget* pRenderTarget)
{
#ifdef _DEBUG
	D2DRenderer::GetInstance()->DrawAABB(*aabb);
	D2DRenderer::GetInstance()->DrawCircle(*circle);
#endif
}

void CircleCollider::ProcessBlock(Collider* ownedComponent, Collider* otherComponent)
{
	__super::ProcessBlock(ownedComponent, otherComponent);
}
