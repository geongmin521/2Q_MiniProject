#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/DataManager.h"

class EnemyBase :
    public GameObject
{
private:
    
public:
    EnemyBase();
    virtual ~EnemyBase();

    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
    void ExploreTarget(EnemyBase* enemy, std::vector<GameObject*>& objs);
public:
    // 일단 퍼블릭
    GameObject* target = nullptr;
    std::vector<GameObject*> objs;
    bool isAttack = false;
    EnemyData enemyData;
};

