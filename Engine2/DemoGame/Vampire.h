#pragma once
#include "EnemyBase.h"
#include "IColliderNotify.h"
#include "BoxCollider.h"


class Vampire :
    public EnemyBase , public IColliderNotify
{
private:

public:
    Vampire(EnemyData data);
    virtual ~Vampire();

    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
    virtual void Attack(float deltaTime) override;

    virtual void OnBlock(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnStayOverlap(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnEndOverlap(Collider* ownedComponent, Collider* otherComponent) override;
};

