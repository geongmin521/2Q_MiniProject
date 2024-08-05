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

public:
    // 일단 퍼블릭

    EnemyData enemyData;
};

