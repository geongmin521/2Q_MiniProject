#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/DataManager.h"
#include "../D2DEngine/IDamageNotify.h"
class TowerBase :
    public GameObject , IDamageNotify
{
private:
    

public:
    
    GameObject* target = nullptr ;
    std::vector<GameObject*> objs;
    TowerBase();
    virtual ~TowerBase();
    TowerData towerData;
    bool isAttack = false;
    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
    virtual void Attack(float deltaTime); //각타워에서 따로동작할 공격  화살발사, 근접공격 등
    void ExploreTarget(TowerBase* tower,std::vector<GameObject*>& objs); //타워타겟 정하는부분
};
