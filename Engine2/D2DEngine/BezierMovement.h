#pragma once
#include "Component.h"

class Transform;
class BezierMovement : public Component
{
public:
    // 스피드 0.3이적당함
    BezierMovement(Transform* transform, float speed);
   
    virtual ~BezierMovement() = default;
    Transform* transform;
    GameObject* target;
    MathHelper::Vector2F preDir; // 회전을위해 필요한거
    MathHelper::Vector2F curDir; // 회전을위해 필요한거
    MathHelper::Vector2F position[3];
    float t;
    float ellipsedTime;
    float speed;

    MathHelper::Vector2F SetMidPoint()
    {
        position[0] = transform->GetWorldLocation();
        position[2] = target->GetWorldLocation();
        float height = (position[2].x - position[0].x) / 5;

        MathHelper::Vector2F mid =  (position[2] + position[0]) / 2;
        mid.y += -((position[2].x - position[0].x) / 5);

        return mid;
    };

    MathHelper::Vector2F QuadraticBezierPoint(float t)
    {
        MathHelper::Vector2F p0 = LinearInterpolate(t, position[0], position[1]);
        MathHelper::Vector2F p1 = LinearInterpolate(t, position[1], position[2]);

        return MathHelper::Vector2F((1 - t) * p0.x, (1 - t) * p0.y) + MathHelper::Vector2F(t * p1.x, t * p1.y);
    }

    MathHelper::Vector2F LinearInterpolate(float t, MathHelper::Vector2F p0, MathHelper::Vector2F p1)
    {
        return MathHelper::Vector2F((1 - t) * p0.x, (1 - t) * p0.y) + MathHelper::Vector2F(t * p1.x, t * p1.y);
    }
    virtual void Update(float deltaTime);
   
};