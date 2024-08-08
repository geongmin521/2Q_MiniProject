#pragma once
#include "TowerBase.h"
class HolyTower : public TowerBase
{
private:

public:
    HolyTower();
    virtual ~HolyTower();

    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
    virtual void Attack(float deltaTime) override;
};

