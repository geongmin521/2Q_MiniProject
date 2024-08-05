#pragma once
#include "TowerBase.h"
#include "../D2DEngine/IColliderNotify.h"

class ArrowTower : public TowerBase, public IColliderNotify
{
private:

public:
    ArrowTower();
    virtual ~ArrowTower();
    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);

    virtual void OnBlock(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnStayOverlap(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnEndOverlap(Collider* ownedComponent, Collider* otherComponent) override;
};

