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
    preDir = curDir;
    ellipsedTime += deltaTime;
    t = ellipsedTime / speed;
    if (t >= 1.0f)
    {
        t = 1;//����� ���ϸ� �ð��� 1�̸� �����߱⶧����..
        //�Ѿ��� ���ֱ�..
        
     
    }
   
    position[2] = target->GetWorldLocation(); //Ÿ���� �������� ����ó���� ����ϴ°���? 
    transform->SetRelativeLocation(QuadraticBezierPoint(t));
    curDir = transform->GetRelativeLocation();
    float moveX = curDir.x - preDir.x;
    float moveY = curDir.y - preDir.y;
    float moveR = atan2(moveY, moveX) * (180.0f / PI);  //ȸ���� ��������ϱ� 
    transform->SetRelativeRotation(moveR);
  
};