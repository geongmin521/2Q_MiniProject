#pragma once
#include "GameObject.h"

class Arrow : public GameObject
{
private:
    float speed = 0.3f;
public:
    Arrow( float speed, std::wstring imagePath);
    virtual ~Arrow();
    
    float ellipsedTime;
    GameObject* target;
    void Init(GameObject* target, MathHelper::Vector2F location); 
    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
};

