#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "BezierMovement.h"

BezierMovement::BezierMovement(Transform* transform, float speed, GameObject* target)
{
    this->transform = transform;
    this->speed = speed;
    this->target = target;
    position[1] = SetMidPoint();
}

void BezierMovement::Update(float deltaTime)
{
    preDir = transform->GetRelativeLocation();
    ellipsedTime += deltaTime;
    t = ellipsedTime / speed;
    if (t >= 1.0f)
    {
        t = 1;
    }
    float moveX = curDir.x - preDir.x;
    float moveY = curDir.y - preDir.y;
    float moveR = atan2(moveY, moveX) * (180.0f / PI);
    position[2] = target->GetWorldLocation();
    transform->SetRelativeRotation(moveR);
    transform->SetRelativeLocation(QuadraticBezierPoint(t));
    curDir = transform->GetRelativeLocation();
};