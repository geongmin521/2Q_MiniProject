#pragma once
#include "EnemyBase.h"
#include "../D2DEngine/IColliderNotify.h"

class VampireBomb
	: public EnemyBase, public IColliderNotify
{
private:
	AABB* attackBox;
public:
	VampireBomb();
	virtual ~VampireBomb();

	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);

	virtual void OnBlock(Collider* ownedComponent, Collider* otherComponent) override;
	virtual void OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent) override;
	virtual void OnStayOverlap(Collider* ownedComponent, Collider* otherComponent) override;
	virtual void OnEndOverlap(Collider* ownedComponent, Collider* otherComponent) override;
	virtual void Attack(float deltaTime) override;
};

