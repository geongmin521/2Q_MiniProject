#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Data.h"
#include "../D2DEngine/IDamageNotify.h"
#include "../D2DEngine/IDragAble.h"
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/Collider.h"
#include "../D2DEngine/UI.h"
class Container;
class TowerBase :
    public GameObject ,public IDamageNotify , public IDragAble //�̷� ������ public�� �Ⱥٿ�����.. ���.. ������� ������Ʈ�� �巡���Ҽ��־�. 
{
private:
   

public:
    Container* container;
    bool isMoving;//�ϴ� ���� �ܼ��� bool������ ó���ϱ�
    
    Bitmap* star;
    float curHP; //Ÿ�����ڰ� ���� ���� ü��
    GameObject* target = nullptr;
    std::vector<GameObject*> targets;
    TowerBase(TowerData data);
    virtual ~TowerBase() = default;
    TowerData towerData;
    bool isAttack = false;

    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
    virtual void FindTarget(Collider* col, bool isTargets = false, bool isHeal =false); 
    virtual void Attack(float deltaTime); //��Ÿ������ ���ε����� ����  ȭ��߻�, �������� ��
    virtual void Hit(float damage) override;
    virtual void Heal(float heal)override; //�ִ�ü�³ѱ�� �ִ�ü�µǰԲ�

    std::vector<ArtifactData> ownedArtifact;

    virtual void BeginDrag(const MouseState& state) override;
    virtual void StayDrag(const MouseState& state) override;
    virtual void EndDrag(const MouseState& state) override;
};
