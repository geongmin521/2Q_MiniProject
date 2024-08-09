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
    float curHP; //Ÿ�����ڰ� ���� ���� ü��
    GameObject* target = nullptr;
    std::vector<GameObject*> targets;
    TowerBase(TowerData data);
    virtual ~TowerBase();
    TowerData towerData;
    bool isAttack = false;

    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
    virtual void FindTarget(Collider* col, bool isTargets = false, bool isHeal =false); 
    virtual void Attack(float deltaTime); //��Ÿ������ ���ε����� ����  ȭ��߻�, �������� ��
    virtual void Hit(float damage) override;
    virtual void Heal(float heal)override; //�ִ�ü�³ѱ�� �ִ�ü�µǰԲ�

    std::vector<ArtifactData> ownedArtifact;
};
