#pragma once
#include "../D2DEngine/GameObject.h"

class TowerBase :
    public GameObject
{
private:
public:

    TowerBase();
    virtual ~TowerBase();
    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
};

