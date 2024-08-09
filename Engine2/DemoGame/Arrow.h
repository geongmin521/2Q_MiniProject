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
    float t; //����ð�
    float sec; //�����ҋ����� �ɸ��� �ð�
    float height; // p1��ǥ�� ����
    MathHelper::Vector2F preDir; // ȸ�������� �ʿ��Ѱ�
    MathHelper::Vector2F curDir; // ȸ�������� �ʿ��Ѱ�
    MathHelper::Vector2F position[3];
    void Init(GameObject* target, MathHelper::Vector2F location); 
    virtual void Update(float deltaTime);
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);

    //mid�� ���ϴ� �Լ�
    MathHelper::Vector2F QuadraticBezierPoint(float t, MathHelper::Vector2F position[]);  
    MathHelper::Vector2F LinearInterpolate(float t, MathHelper::Vector2F p0, MathHelper::Vector2F p1);
};
