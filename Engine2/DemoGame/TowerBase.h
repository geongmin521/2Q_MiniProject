#pragma once
#include "GameObject.h"
#include "Data.h"
#include "IDamageNotify.h"
#include "IDragAble.h"
#include "Bitmap.h"
#include "Collider.h"
#include "IClickAble.h"
#include "UI.h"


enum class TowerType
{
    Crossbow,
    Water,
    Pile,
    HolyCross
}; 

class Container;
class TowerStar;
class HPBar;
class TowerBase :
    public GameObject , public IDamageNotify , public IDragAble, public IColliderNotify, public IClickAble
{
public: //나중에 은닉화할 데이터는 빼기
    TowerData towerData;   
    Container* container; //본인이 담겨있는 컨테이너.. 
    std::vector<GameObject*> target;
    std::function<void(void)> Search; //아이디로 타입구분해서 각각의 타워에 맞는 기능을 넣어주기
    std::function<void(void)> AttackFunc;
public:
    float curHP;        //타워각자가 가질 현재 체력 //hp 참조로 넘겨주면될듯? 그럼 게임오브젝트에 필요없겠지? 

    TowerBase(TowerData data);
    virtual ~TowerBase() = default; //진짜 어떻게 해야할지를 모르겠네 허 허.. //불렛만 다르면 되는거지 적 불렛이랑 다른게 뭐지?  

    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);

    virtual void Attack(float deltaTime); //각타워에서 따로동작할 공격  화살발사, 근접공격 등
    virtual void Hit(float damage);
    virtual void Heal(float heal); //최대체력넘기면 최대체력되게끔

    virtual void BeginDrag(const MouseState& state) override;
    virtual void StayDrag(const MouseState& state) override;
    virtual void EndDrag(const MouseState& state) override;

    virtual void OnBlock(Collider* ownedComponent, Collider* otherComponent)        override;
    virtual void OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)  override;
    virtual void OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)   override;

    virtual void OnClick() override;
};
