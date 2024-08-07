#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/DataManager.h"
#include "../D2DEngine/Collider.h"
class EnemyBase :
    public GameObject
{
private:
    
public:
    EnemyBase();
    virtual ~EnemyBase();

    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
    virtual void Find(Collider* othercomponent);
public:
    // 일단 퍼블릭
    GameObject* target = nullptr;
    bool isAttack = false;
    EnemyData enemyData;
};

