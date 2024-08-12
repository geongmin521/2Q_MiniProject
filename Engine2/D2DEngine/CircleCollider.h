#pragma once
#include "Collider.h"

class AABB;
class Circle;
class IColliderNotify;
class CircleCollider :
    public Collider
{
public:
	AABB* aabb; //박스콜라이더랑 충돌할때는 이걸로 계산하기
	Circle* circle;

	CircleCollider(AABB* aabb, Circle* circle, CollisionType type, IColliderNotify* notify, CollisionLayer layer);
	~CircleCollider();
	virtual bool IsCollide(Collider* otherComponent) override;
	virtual void Render(ID2D1RenderTarget* pRenderTarget,float Alpha = 1) override;
	virtual void Update(float deltaTime)override;
	virtual	void ProcessBlock(Collider* ownedComponent,Collider* otherComponent) override;
};

