#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "BezierMovement.h"

BezierMovement::BezierMovement(Transform* transform, float speed)
{
    this->transform = transform;
    this->speed = speed;
}

void BezierMovement::Update(float deltaTime)
{
    if (target == nullptr) //타겟이 아직없다면 넘기고
        return;
    position[1] = SetMidPoint(); //나중에 이것도 좀 손봐야할거같은데.. 
    preDir = transform->GetRelativeLocation();
    ellipsedTime += deltaTime;
    t = ellipsedTime / speed;
    if (t >= 1.0f)
    {
        t = 1;//베지어에 의하면 시간이 1이면 도착했기때문에..
        //총알을 없애기..
        owner->SetActive(false);
    }
    float moveX = curDir.x - preDir.x;
    float moveY = curDir.y - preDir.y;
    float moveR = atan2(moveY, moveX) * (180.0f / PI);
    position[2] = target->GetWorldLocation(); //타겟이 없을때의 예외처리는 어디서하는거지? 
    transform->SetRelativeRotation(moveR);
    transform->SetRelativeLocation(QuadraticBezierPoint(t));
    curDir = transform->GetRelativeLocation();
};