#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Data.h"
#include "../D2DEngine/IDamageNotify.h"
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/Collider.h"
class TowerBase :
    public GameObject , IDamageNotify
{
private:
    

public:
    
    Bitmap* star;
    float curHP; //타워각자가 가질 현재 체력
    GameObject* target = nullptr;
    std::vector<GameObject*> targets;
    TowerBase(TowerData data);
    virtual ~TowerBase();
    TowerData towerData;
    bool isAttack = false;

    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
    virtual void FindTarget(Collider* col, bool isTargets = false, bool isHeal =false); 
    virtual void Attack(float deltaTime); //각타워에서 따로동작할 공격  화살발사, 근접공격 등
    virtual void Hit(float damage) override;
    virtual void Heal(float heal)override; //최대체력넘기면 최대체력되게끔

    std::vector<ArtifactData> ownedArtifact;
};
