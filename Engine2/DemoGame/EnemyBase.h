#pragma once
#include "GameObject.h"
#include "DataManager.h"
#include "Collider.h"
#include "IDamageNotify.h"
#include "IColliderNotify.h"

class HPBar;
class TowerBase;
class EnemyBase :
    public GameObject , IDamageNotify, IColliderNotify
{
private:
    std::function<void(void)> attack;
public:
    EnemyBase(EnemyData data);
    void SetAbility(std::string ability);
    virtual ~EnemyBase();
    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha =1);
    virtual void Hit(float damage);
    virtual void Heal(float heal)override {}
    virtual void Attack();

    virtual void OnBlock(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnStayOverlap(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnEndOverlap(Collider* ownedComponent, Collider* otherComponent) override;
public:
    float curHP;
    std::vector<GameObject*> target; 
    EnemyData enemyData;
};

