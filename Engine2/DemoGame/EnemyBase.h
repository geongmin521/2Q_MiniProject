#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/DataManager.h"
#include "../D2DEngine/Collider.h"
#include "../D2DEngine/IDamageNotify.h"
class EnemyBase :
    public GameObject , IDamageNotify
{
private:
    
public:
    EnemyBase();
    virtual ~EnemyBase();

    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
    virtual void Find(Collider* othercomponent);
    virtual void Hit(float damage) { curHP -= damage; }
public:
    // 일단 퍼블릭
    float curHP;
    GameObject* target = nullptr;
    bool isAttack = false;
    EnemyData enemyData;
};

