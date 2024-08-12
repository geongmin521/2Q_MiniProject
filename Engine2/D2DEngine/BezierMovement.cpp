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
    if (target == nullptr) //Ÿ���� �������ٸ� �ѱ��
        return;
    position[1] = SetMidPoint(); //���߿� �̰͵� �� �պ����ҰŰ�����.. 
    preDir = transform->GetRelativeLocation();
    ellipsedTime += deltaTime;
    t = ellipsedTime / speed;
    if (t >= 1.0f)
    {
        t = 1;//����� ���ϸ� �ð��� 1�̸� �����߱⶧����..
        //�Ѿ��� ���ֱ�..
        owner->SetActive(false);
    }
    float moveX = curDir.x - preDir.x;
    float moveY = curDir.y - preDir.y;
    float moveR = atan2(moveY, moveX) * (180.0f / PI);
    position[2] = target->GetWorldLocation(); //Ÿ���� �������� ����ó���� ����ϴ°���? 
    transform->SetRelativeRotation(moveR);
    transform->SetRelativeLocation(QuadraticBezierPoint(t));
    curDir = transform->GetRelativeLocation();
};