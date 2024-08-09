#pragma once
#include "GameObject.h"
#include "DataManager.h"
#include "Collider.h"
#include "IDamageNotify.h"

class HPBar;
class EnemyBase :
    public GameObject , IDamageNotify
{
private:
    
public:
    EnemyBase(EnemyData data);
    virtual ~EnemyBase();

    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
    virtual void Find(Collider* othercomponent);
    virtual void Hit(float damage);
    virtual void Heal(float heal)override {}
    virtual void Attack(float deltaTime);
public:
    // �ϴ� �ۺ�
    HPBar* HPbar;
    float curHP;
    GameObject* target = nullptr;
    bool isAttack = false;
    EnemyData enemyData;
    WaveData waveData;
};

