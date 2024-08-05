#pragma once
#include "Component.h"
#include "MathHelper.h"

class Transform;

class Movement :
    public Component
{
public:
	Movement(Transform* target); //이거는 생성자에서 넣어줘야지. 
	virtual ~Movement() = default;
public:
	MathHelper::Vector2F	velocity;		// 속도 벡터
	Transform*				transform;		// 위치를 변경할 컴포넌트
	D2D_VECTOR_2F 			prevRelativeLocation = { 0,0 }; // 이전 위치
public:
	virtual void Update(float deltaTime);
	//렌더를 활성화하면 움직이는 방향으로 보여주기?
	void SetSceneComponent(Transform* val) { transform = val; }
	void SetVelocity(MathHelper::Vector2F velocity) { velocity = velocity; };
	void AddVelocity(MathHelper::Vector2F velocity) { velocity += velocity; };
	void PrevPosition(bool prevX, bool prevY);
	MathHelper::Vector2F GetVelocity() { return velocity; };
	MathHelper::Vector2F GetPrevPos() { return prevRelativeLocation; };
};

