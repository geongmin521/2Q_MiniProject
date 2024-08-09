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
//    float t; //경과시간
//    float sec; //도달할떄까지 걸리는 시간
//    float height; // p1좌표의 높이
//    MathHelper::Vector2F preDir; // 회전을위해 필요한거
//    MathHelper::Vector2F curDir; // 회전을위해 필요한거
//    MathHelper::Vector2F position[3];
//    GameObject* target;         //성수도 적의 이동에따라 따라가나? 아니면 던질때 위치에 투척해서 지속공격?
//    std::vector<GameObject*> targets; //범위공격용
//    void Init(GameObject* target, MathHelper::Vector2F location);
//    virtual void Update(float deltaTime);
//    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
//
//    //mid값 구하는 함수
//
//    MathHelper::Vector2F QuadraticBezierPoint(float t, MathHelper::Vector2F position[]);
//
//    MathHelper::Vector2F LinearInterpolate(float t, MathHelper::Vector2F p0, MathHelper::Vector2F p1);
//
//
//};