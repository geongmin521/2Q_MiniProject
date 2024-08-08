#pragma once
#include "../D2DEngine/GameObject.h"

class Arrow : public GameObject
{
private:
    float speed = 1000.0f;
public:
    Arrow();
    virtual ~Arrow();
    
    float ellipsedTime;
    float t; //경과시간
    float sec; //도달할떄까지 걸리는 시간
    float height; // p1좌표의 높이
    MathHelper::Vector2F position[3];
    GameObject* target;
    void Init(GameObject* target, MathHelper::Vector2F location); 
    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);

    MathHelper::Vector2F QuadraticBezierPoint(float t, MathHelper::Vector2F position[]);
   
    MathHelper::Vector2F LinearInterpolate(float t, MathHelper::Vector2F p0, MathHelper::Vector2F p1);
   
   
};