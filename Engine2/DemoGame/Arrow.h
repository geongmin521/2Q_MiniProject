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
    float t; //����ð�
    float sec; //�����ҋ����� �ɸ��� �ð�
    float height; // p1��ǥ�� ����
    MathHelper::Vector2F preDir; // ȸ�������� �ʿ��Ѱ�
    MathHelper::Vector2F curDir; // ȸ�������� �ʿ��Ѱ�
    MathHelper::Vector2F position[3];
    GameObject* target;
    void Init(GameObject* target, MathHelper::Vector2F location); 
    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);

    //mid�� ���ϴ� �Լ�

    MathHelper::Vector2F QuadraticBezierPoint(float t, MathHelper::Vector2F position[]);
   
    MathHelper::Vector2F LinearInterpolate(float t, MathHelper::Vector2F p0, MathHelper::Vector2F p1);
   
   
};

//class Bezier
//{
//public:
//
//    MathHelper::Vector2F SetMidPoint()
//    {
//
//    };
//    MathHelper::Vector2F QuadraticBezierPoint(float t, MathHelper::Vector2F position[])
//    {
//        MathHelper::Vector2F p0 = LinearInterpolate(t, position[0], position[1]);
//        MathHelper::Vector2F p1 = LinearInterpolate(t, position[1], position[2]);
//
//        return MathHelper::Vector2F((1 - t) * p0.x, (1 - t) * p0.y) + MathHelper::Vector2F(t * p1.x, t * p1.y);
//    }
//
//    MathHelper::Vector2F LinearInterpolate(float t, MathHelper::Vector2F p0, MathHelper::Vector2F p1)
//    {
//        return MathHelper::Vector2F((1 - t) * p0.x, (1 - t) * p0.y) + MathHelper::Vector2F(t * p1.x, t * p1.y);
//    }
//    virtual void Update();
//};