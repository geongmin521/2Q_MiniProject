#pragma once
#include "Collider.h"
#include "Component.h"
class AABB;
class IColliderNotify;
class BoxCollider :public Collider, public Component
{
public:
	BoxCollider(AABB* aabb, CollisionType type, IColliderNotify* notify, CollisionLayer layer);
	~BoxCollider();
	AABB* aabb;

	virtual bool IsCollide   (Collider* ownedComponent) override; //어? 이거 자체는 상대꺼만 들어오면되잖아.. 
	virtual	void ProcessBlock(Collider* ownedComponent, Collider* otherComponent) override;
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1RenderTarget* pRenderTarget) override;
};

