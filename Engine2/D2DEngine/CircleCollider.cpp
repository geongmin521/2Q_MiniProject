#include "pch.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "AABB.h"
#include "Circle.h"
#include "D2DRenderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "CollisionManager.h"

CircleCollider::CircleCollider(AABB* aabb, Circle* circle, CollisionType type, IColliderNotify* notify, CollisionLayer layer) :Collider(type, notify, layer)
{ 
	colliderType = ColliderType::Circle;
	this->aabb = aabb;
	this->circle = circle;
}

CircleCollider::~CircleCollider()
{
}

bool CircleCollider::IsCollide(Collider* otherComponent)
{
	if (otherComponent->GetColliderType() == ColliderType::Box)
	{
		return  aabb->CheckIntersect(*((BoxCollider*)otherComponent)->aabb);
	}
	else if(otherComponent->GetColliderType() == ColliderType::Circle)
	{
		return  circle->CheckIntersect(*((CircleCollider*)otherComponent)->circle);
	}
	
}

void CircleCollider::Update(float deltaTime)
{
	if (owner->transform)
	{
		aabb->Center = owner->transform->GetWorldLocation(); 
		aabb->Center += offset;
		circle->Center = owner->transform->GetWorldLocation();
		circle->Center += offset;
	}
}

void CircleCollider::Render(ID2D1RenderTarget* pRenderTarget,float Alpha)
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
