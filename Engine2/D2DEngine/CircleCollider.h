#pragma once
#include "Collider.h"

class AABB;
class Circle;
class IColliderNotify;
class CircleCollider :
    public Collider
{
public:
	AABB* aabb; //박스콜라이더를 만날때는 aabb
	Circle* circle;
	MathHelper::Vector2F offset = {0,0};
	CircleCollider(AABB* aabb, Circle* circle, CollisionType type, IColliderNotify* notify, CollisionLayer layer);
	~CircleCollider();
	virtual bool IsCollide(Collider* otherComponent) override;
	virtual void Render(ID2D1RenderTarget* pRenderTarget,float Alpha = 1) override;
	virtual void Update(float deltaTime)override;
	virtual	void ProcessBlock(Collider* ownedComponent,Collider* otherComponent) override;
	void SetOffset(MathHelper::Vector2F offset) { this->offset = offset; }
};

