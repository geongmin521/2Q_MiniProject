#pragma once
#include "GameObject.h"
#include "Data.h"
#include "IDamageNotify.h"
#include "IDragAble.h"
#include "Bitmap.h"
#include "Collider.h"
#include "UI.h"
#include "TowerStar.h"
#include "HPBar.h"
class Container;

class TowerBase :
    public GameObject ,public IDamageNotify , public IDragAble //이런 개같은 public을 안붙였었네.. 됬다.. 이제모든 오브젝트도 드래그할수있어. 
{
private:
   

public:

    Container* container;
    bool isMoving;//일단 제일 단순한 bool값으로 처리하기
    TowerStar* star; //기본타워에서 star하나씩가지고있게
    HPBar* HPbar;
    float curHP; //타워각자가 가질 현재 체력
    GameObject* target = nullptr;
    std::vector<GameObject*> targets;
    TowerBase(TowerData data);
    virtual ~TowerBase() = default;
    TowerData towerData;
    bool isAttack = false;

    float testEffect;

    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
    virtual void FindTarget(Collider* col, bool isTargets = false, bool isHeal =false); 
    virtual void Attack(float deltaTime); //각타워에서 따로동작할 공격  화살발사, 근접공격 등
    virtual void Hit(float damage) override;
    virtual void Heal(float heal)override; //최대체력넘기면 최대체력되게끔

    std::vector<ArtifactData> ownedArtifact;

    virtual void BeginDrag(const MouseState& state) override;
    virtual void StayDrag(const MouseState& state) override;
    virtual void EndDrag(const MouseState& state) override;
};
