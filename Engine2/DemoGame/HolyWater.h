//#pragma once
//#include "../D2DEngine/GameObject.h"
//
//class HolyWater : public GameObject
//{
//private:
//    float speed = 500.0f;
//public:
//    HolyWater();
//    virtual ~HolyWater();
//
//    float ellipsedTime;
//    float t; //����ð�
//    float sec; //�����ҋ����� �ɸ��� �ð�
//    float height; // p1��ǥ�� ����
//    MathHelper::Vector2F preDir; // ȸ�������� �ʿ��Ѱ�
//    MathHelper::Vector2F curDir; // ȸ�������� �ʿ��Ѱ�
//    MathHelper::Vector2F position[3];
//    GameObject* target;         //������ ���� �̵������� ���󰡳�? �ƴϸ� ������ ��ġ�� ��ô�ؼ� ���Ӱ���?
//    std::vector<GameObject*> targets; //�������ݿ�
//    void Init(GameObject* target, MathHelper::Vector2F location);
//    virtual void Update(float deltaTime);
//    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
//
//    //mid�� ���ϴ� �Լ�
//
//    MathHelper::Vector2F QuadraticBezierPoint(float t, MathHelper::Vector2F position[]);
//
//    MathHelper::Vector2F LinearInterpolate(float t, MathHelper::Vector2F p0, MathHelper::Vector2F p1);
//
//
//};