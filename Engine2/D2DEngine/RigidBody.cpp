#include "pch.h"
#include "Transform.h"
#include "D2DRenderer.h"
#include "RigidBody.h"
#include "AABB.h"

RigidBody::RigidBody()
{
	Enable();
}

RigidBody::~RigidBody()
{
}

void RigidBody::Update(float deltaTime)
{
	if (isGravity)
		gravityScale += 0.098; //중력가속도로 계속더해짐 델타타임은 무브먼트에서 더해질거임
}

void RigidBody::Enable()
{
	isGravity = true;
	gravityScale = 0;
}

void RigidBody::Disable()
{
	gravityScale = 0;
}

