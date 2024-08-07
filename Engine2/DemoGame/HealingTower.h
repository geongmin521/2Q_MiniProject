#pragma once
#include "TowerBase.h"
#include "../D2DEngine/IColliderNotify.h"
class HealingTower : public TowerBase, IColliderNotify
{
private:

public:
    HealingTower();
    virtual ~HealingTower();

    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
    virtual void Attack(float deltaTime) override;
    virtual void OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnStayOverlap(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnEndOverlap(Collider* ownedComponent, Collider* otherComponent) override;

};