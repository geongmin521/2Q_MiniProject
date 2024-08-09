#pragma once
#include "../D2DEngine/GameObject.h"

class Arrow : public GameObject
{
private:
    float speed = 1000.0f;
public:
    Arrow();
    virtual ~Arrow();
    
    GameObject* target;
    void Init(MathHelper::Vector2F velocity, MathHelper::Vector2F location); //����, ��ġ?
    void Inits(GameObject* target, MathHelper::Vector2F location); //����, ��ġ?
    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);

};