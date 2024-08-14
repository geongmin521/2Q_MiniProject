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
		gravityScale += 0.098; 
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

