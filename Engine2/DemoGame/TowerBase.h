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
public: //���߿� ����ȭ�� �����ʹ� ����
    TowerData towerData;   
    Container* container; //������ ����ִ� �����̳�.. 
    std::vector<GameObject*> target;
    std::function<void(void)> Search; //���̵�� Ÿ�Ա����ؼ� ������ Ÿ���� �´� ����� �־��ֱ�
    std::function<void(void)> AttackFunc;
    float cooldown = 0;

    // ����ϴ� �͵�
    bool hitEffct = false;
    float hitEffctDelay = 0.0f;

    HPBar* hpbar;
    float curHP;        //Ÿ�����ڰ� ���� ���� ü�� //hp ������ �Ѱ��ָ�ɵ�? �׷� ���ӿ�����Ʈ�� �ʿ������? 
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
    virtual ~TowerBase() = default; //��¥ ��� �ؾ������� �𸣰ڳ� �� ��.. //�ҷ��� �ٸ��� �Ǵ°��� �� �ҷ��̶� �ٸ��� ����?  

    //TowerBase mainTower
    //bool ���
    // ��ᰡ Ʈ��Ǹ� ����Ÿ���� ��
    // ���� ������
    // ���Ÿ�� �ռ�(mainTower)
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

    virtual void OnDoubleClick() override;

    virtual void OnMouse() override;
    virtual void OutMouse() override;
};
