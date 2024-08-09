#pragma once
#include "GameObject.h"

class Arrow : public GameObject
{
private:
    float speed = 1000.0f;
    GameObject* target = nullptr;
public:
    Arrow();
    virtual ~Arrow();
    
    float ellipsedTime;
    float t; //경과시간
    float sec; //도달할떄까지 걸리는 시간
    float height; // p1좌표의 높이
    MathHelper::Vector2F preDir; // 회전을위해 필요한거
    MathHelper::Vector2F curDir; // 회전을위해 필요한거
    MathHelper::Vector2F position[3];
    void Init(GameObject* target, MathHelper::Vector2F location); 
    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);

    //mid값 구하는 함수
    MathHelper::Vector2F QuadraticBezierPoint(float t, MathHelper::Vector2F position[]);  
    MathHelper::Vector2F LinearInterpolate(float t, MathHelper::Vector2F p0, MathHelper::Vector2F p1);
};
