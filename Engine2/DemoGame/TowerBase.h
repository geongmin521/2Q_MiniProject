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
    public GameObject , public IDamageNotify , public IDragAble, public IDoubleClickAble, public IOnMouse
{
public: //나중에 은닉화할 데이터는 빼기
    TowerData towerData;   
    Container* container; //본인이 담겨있는 컨테이너.. 
    std::vector<GameObject*> target;
    std::function<void(void)> Search; //아이디로 타입구분해서 각각의 타워에 맞는 기능을 넣어주기
    std::function<void(void)> AttackFunc;
    float cooldown = 0;

    // 사용하는 것들
    bool hitEffct = false;
    float hitEffctDelay = 0.0f;

    HPBar* hpbar;
    float curHP;        //타워각자가 가질 현재 체력 //hp 참조로 넘겨주면될듯? 그럼 게임오브젝트에 필요없겠지? 
    float prevHp;
    float maxHP;
    float knockBack;

    float doubleTime = 0;
    float curSpeed;
    bool isMerge = false;
    bool isMerged = false;
    float alpha = 1.0f;
    float mergeTime = 0;
public:
    
    TowerBase(TowerData data);
    virtual ~TowerBase() = default; //진짜 어떻게 해야할지를 모르겠네 허 허.. //불렛만 다르면 되는거지 적 불렛이랑 다른게 뭐지?  

    //TowerBase mainTower
    //bool 재료
    // 재료가 트루되면 메인타워로 가
    // 가서 없어져
    // 재료타워 합성(mainTower)
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

    virtual void OnDoubleClick() override;

    virtual void OnMouse() override;
    virtual void OutMouse() override;
};
