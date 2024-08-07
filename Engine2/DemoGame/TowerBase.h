#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/DataManager.h"
#include "../D2DEngine/IDamageNotify.h"
#include "../D2DEngine/Collider.h"
class TowerBase :
    public GameObject , IDamageNotify
{
private:
    

public:
    float curHP; //타워각자가 가질 현재 체력
    GameObject* target = nullptr;      //원거리타워등 단일공격
    std::vector<GameObject*> targets;  //근접타워용등 여러명 공격 따로 뺄까
    TowerBase();
    virtual ~TowerBase();
    TowerData towerData;
    bool isAttack = false;
    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
    virtual void FindTarget(Collider* col, bool isTargets = false); 
    virtual void Attack(float deltaTime); //각타워에서 따로동작할 공격  화살발사, 근접공격 등
    virtual void Hit(float damage) { curHP -= damage; }
};
