#pragma once
#include "GameObject.h"
#include "Data.h"
#include "IDamageNotify.h"
#include "IDragAble.h"
#include "Bitmap.h"
#include "Collider.h"
#include "IDoubleClickAble.h"
#include "IOnMouse.h"
#include "UI.h"


enum class TowerType
{
    Crossbow,
    Water,
    Pile,
    HolyCross,
    Hidden
}; 

class Container;
class TowerStar;
class ToolTip;
class HPBar;
class TowerBase :
    public GameObject , public IDamageNotify , public IDragAble, public IColliderNotify, public IDoubleClickAble, public IOnMouse
{
public: //나중에 은닉화할 데이터는 빼기
    TowerData towerData;   
    ToolTip* toolTip; //하나만 필요하긴한데.. 모든 객체가 들고있는게 그냥 불편함.. 
    Container* container; //본인이 담겨있는 컨테이너.. 
    std::vector<GameObject*> target;
    std::function<void(void)> Search; //아이디로 타입구분해서 각각의 타워에 맞는 기능을 넣어주기
    std::function<void(void)> AttackFunc;
    //test 이펙트
    bool hitEffct = false;
    float hitEffctDelay = 0.0f;

    HPBar* hpbar;
    float curHP;        //타워각자가 가질 현재 체력 //hp 참조로 넘겨주면될듯? 그럼 게임오브젝트에 필요없겠지? 
    float prevHp;

    float curRange;
public:
    
    TowerBase(TowerData data);
    virtual ~TowerBase() = default; //진짜 어떻게 해야할지를 모르겠네 허 허.. //불렛만 다르면 되는거지 적 불렛이랑 다른게 뭐지?  

    void Init(MathHelper::Vector2F pos);

    void StatUpdate();

    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha =1);

    virtual void Attack(float deltaTime); //각타워에서 따로동작할 공격  화살발사, 근접공격 등
    virtual void Hit(float damage, float knockback = 0);
    virtual void Heal(float heal); //최대체력넘기면 최대체력되게끔

    virtual void BeginDrag(const MouseState& state) override;
    virtual void StayDrag(const MouseState& state) override;
    virtual void EndDrag(const MouseState& state) override;
    virtual void FailDrop() override;

    virtual void OnBlock(Collider* ownedComponent, Collider* otherComponent)        override;
    virtual void OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent) override;
    virtual void OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)  override;
    virtual void OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)   override;

    virtual void OnDoubleClick() override;

    virtual void OnMouse() override;
    virtual void OutMouse() override;
};
