#pragma once
#include "TowerBase.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/IColliderNotify.h"
#include "Arrow.h"
class ArrowTower : public TowerBase, public IColliderNotify 
{
private:

public:
    ArrowTower(TowerData data);
    virtual ~ArrowTower() = default;

    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
    virtual void Attack(float deltaTime) override;
    virtual void OnBlock(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnStayOverlap(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnEndOverlap(Collider* ownedComponent, Collider* otherComponent) override;

    virtual void BeginDrag(const MouseState& state) override;
    virtual void StayDrag(const MouseState& state) override;
    virtual void EndDrag(const MouseState& state) override;
    
};


