#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/DataManager.h"
#include "../D2DEngine/IDamageNotify.h"
#include "../D2DEngine/Collider.h"
class TowerBase :
    public GameObject , IDamageNotify
{
private:
    

public:
    float curHP; //Ÿ�����ڰ� ���� ���� ü��
    GameObject* target = nullptr;      //���Ÿ�Ÿ���� ���ϰ���
    std::vector<GameObject*> targets;  //����Ÿ����� ������ ���� ���� ����
    TowerBase();
    virtual ~TowerBase();
    TowerData towerData;
    bool isAttack = false;
    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
    virtual void FindTarget(Collider* col, bool isTargets = false); 
    virtual void Attack(float deltaTime); //��Ÿ������ ���ε����� ����  ȭ��߻�, �������� ��
    virtual void Hit(float damage) { curHP -= damage; }
};
