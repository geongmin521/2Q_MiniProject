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
    public GameObject ,public IDamageNotify , public IDragAble //�̷� ������ public�� �Ⱥٿ�����.. ���.. ������� ������Ʈ�� �巡���Ҽ��־�. 
{
private:
   

public:

    Container* container;
    bool isMoving;//�ϴ� ���� �ܼ��� bool������ ó���ϱ�
    TowerStar* star; //�⺻Ÿ������ star�ϳ����������ְ�
    HPBar* HPbar;
    float curHP; //Ÿ�����ڰ� ���� ���� ü��
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
    virtual void Attack(float deltaTime); //��Ÿ������ ���ε����� ����  ȭ��߻�, �������� ��
    virtual void Hit(float damage) override;
    virtual void Heal(float heal)override; //�ִ�ü�³ѱ�� �ִ�ü�µǰԲ�

    std::vector<ArtifactData> ownedArtifact;

    virtual void BeginDrag(const MouseState& state) override;
    virtual void StayDrag(const MouseState& state) override;
    virtual void EndDrag(const MouseState& state) override;
};
