#pragma once
#include "Component.h"
using namespace MathHelper;
class Transform;
class BezierMovement : public Component
{
public:
    BezierMovement(Transform* transform, float speed);
   
    virtual ~BezierMovement() = default;
    Transform* transform;
    GameObject* target;
    Vector2F preDir; // 회전을위해 필요한거
    Vector2F curDir; // 회전을위해 필요한거
    Vector2F position[3];
    float t;
    float ellipsedTime;
    float speed;

    Vector2F SetMidPoint()
    {
        position[0] = transform->GetWorldLocation();
        position[2] = target->GetWorldLocation();
        float height = (position[2].x - position[0].x) / 5;

        Vector2F mid =  (position[2] + position[0]) / 2;
        mid.y += -((position[2].x - position[0].x) / 5);

        return mid;
    };

    Vector2F QuadraticBezierPoint(float t)
    {
        Vector2F p0 = LinearInterpolate(t, position[0], position[1]);
        Vector2F p1 = LinearInterpolate(t, position[1], position[2]);

        return Vector2F((1 - t) * p0.x, (1 - t) * p0.y) + Vector2F(t * p1.x, t * p1.y);
    }

    Vector2F LinearInterpolate(float t, Vector2F p0, Vector2F p1)
    {
        return Vector2F((1 - t) * p0.x, (1 - t) * p0.y) + Vector2F(t * p1.x, t * p1.y);
    }
    virtual void Update(float deltaTime);
   
};