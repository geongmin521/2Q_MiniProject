#pragma once
#include "TowerBase.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/IColliderNotify.h"
#include "Arrow.h"
class ArrowTower : public TowerBase, public IColliderNotify
{
private:
    float attacktime = 1.0f; // �ӽ÷� ����Ÿ�� ���ݽ����
    std::vector<Arrow*> arrows; //����ü �⺻�δ� �׳� �ش�Ÿ������ �ֱ�? attack�Լ��� ���� ������༭ �� Ÿ������ �ٸ��� �����ϰԲ�?
public:
    ArrowTower();
    virtual ~ArrowTower();

    BoxCollider* searchBound;
    BoxCollider* towerBound;

    AABB* attackRange;
    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
    virtual void Attack(float deltaTime) override;
    virtual void Find() override;
    virtual void OnBlock(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnStayOverlap(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnEndOverlap(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void Hit(GameObject* obj)override;
    
};


