#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/DataManager.h"
class TowerBase :
    public GameObject
{
private:
    

public:
    
    GameObject* target = nullptr ;
    std::vector<GameObject*> objs;
    TowerBase();
    virtual ~TowerBase();
    TowerData towerData;
    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
    virtual void Attack(float deltaTime); //��Ÿ������ ���ε����� ����  ȭ��߻�, �������� ��
    void ExploreTarget(TowerBase& tower,std::vector<GameObject*>& objs); //Ÿ��Ÿ�� ���ϴºκ�
};
