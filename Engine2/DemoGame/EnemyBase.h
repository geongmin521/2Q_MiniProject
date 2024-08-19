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
    std::function<void(void)> Ability;
public:
    bool isHited = false; //맞았다를 머라하지
    bool isSpawned = false;
    float spawnTime = 0;
    float hitedTime = 0.35f; //잠시만 밀리면되니까
    float elapsedTime = 0;
    EnemyBase(EnemyData data);
    void SetAbility(std::string ability);
    virtual ~EnemyBase();
    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha =1);
    virtual void Hit(float damage, float knockback = 0);
    virtual void Heal(float heal)override;
    virtual void Attack();
    void ability();

    virtual void OnBlock(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnStayOverlap(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnEndOverlap(Collider* ownedComponent, Collider* otherComponent) override;
public:
    float curHP;
    float curATK; 
    std::vector<GameObject*> target; 
    EnemyData enemyData;

    //test 이펙트
    bool hitEffct = false;
};

