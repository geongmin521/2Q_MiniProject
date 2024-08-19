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
    bool isHited = false; //�¾Ҵٸ� �Ӷ�����
    bool isSpawned = false;
    float spawnTime = 0;
    float hitedTime = 0.35f; //��ø� �и���Ǵϱ�
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

    //test ����Ʈ
    bool hitEffct = false;
};

