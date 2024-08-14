#pragma once
#include "Collider.h"
#include "Component.h"
class AABB;
class IColliderNotify;
class BoxCollider :public Collider
{
public:
	BoxCollider() = default;
	BoxCollider(AABB* aabb, CollisionType type, IColliderNotify* notify, CollisionLayer layer);
	~BoxCollider();
	AABB* aabb;
	void Init(AABB* aabb, CollisionType type, IColliderNotify* notify, CollisionLayer layer);
	virtual bool IsCollide   (Collider* ownedComponent) override;
	virtual	void ProcessBlock(Collider* ownedComponent, Collider* otherComponent) override;
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1RenderTarget* pRenderTarget,float Alpha = 1) override;
};

