#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/DataManager.h"
class TowerBase :
    public GameObject
{
private:
    

public:

    TowerBase();
    virtual ~TowerBase();
    TowerData towerData;
    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
    virtual void Attack(float deltaTime); //��Ÿ������ ���ε����� ����  ȭ��߻�, �������� ��
};
