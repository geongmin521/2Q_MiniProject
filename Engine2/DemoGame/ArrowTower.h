#pragma once
#include "TowerBase.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/IColliderNotify.h"
#include "Arrow.h"

// test 용
#include "../D2DEngine/D2DFont.h"

class ArrowTower : public TowerBase, public IColliderNotify
{
private:
    float attacktime = 1.0f; // 임시로 어택타임 지금실험용
    std::vector<Arrow*> arrows; //투사체 기본인대 그냥 해당타워에만 넣기? attack함수를 따로 만들어줘서 각 타워에서 다르게 동작하게끔?
public:
    ArrowTower(TowerData data);
    virtual ~ArrowTower();

    BoxCollider* box;
    AABB* attackRange;
    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
    virtual void Attack(float deltaTime) override;
    virtual void OnBlock(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnStayOverlap(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnEndOverlap(Collider* ownedComponent, Collider* otherComponent) override;

    D2DFont test;
    virtual void Hit(GameObject* obj)override;
};


