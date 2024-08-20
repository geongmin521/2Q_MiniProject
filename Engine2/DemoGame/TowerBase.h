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
public: //���߿� ����ȭ�� �����ʹ� ����
    TowerData towerData;   
    ToolTip* toolTip; //�ϳ��� �ʿ��ϱ��ѵ�.. ��� ��ü�� ����ִ°� �׳� ������.. 
    Container* container; //������ ����ִ� �����̳�.. 
    std::vector<GameObject*> target;
    std::function<void(void)> Search; //���̵�� Ÿ�Ա����ؼ� ������ Ÿ���� �´� ����� �־��ֱ�
    std::function<void(void)> AttackFunc;
    //test ����Ʈ
    bool hitEffct = false;
    float hitEffctDelay = 0.0f;

    HPBar* hpbar;
    float curHP;        //Ÿ�����ڰ� ���� ���� ü�� //hp ������ �Ѱ��ָ�ɵ�? �׷� ���ӿ�����Ʈ�� �ʿ������? 
    float prevHp;

    float curRange;
public:
    
    TowerBase(TowerData data);
    virtual ~TowerBase() = default; //��¥ ��� �ؾ������� �𸣰ڳ� �� ��.. //�ҷ��� �ٸ��� �Ǵ°��� �� �ҷ��̶� �ٸ��� ����?  

    void Init(MathHelper::Vector2F pos);

    void StatUpdate();

    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha =1);

    virtual void Attack(float deltaTime); //��Ÿ������ ���ε����� ����  ȭ��߻�, �������� ��
    virtual void Hit(float damage, float knockback = 0);
    virtual void Heal(float heal); //�ִ�ü�³ѱ�� �ִ�ü�µǰԲ�

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
