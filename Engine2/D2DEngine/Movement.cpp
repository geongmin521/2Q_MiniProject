#include "pch.h"
#include "Movement.h"
#include "Transform.h"

Movement::Movement(Transform* target)
{
	velocity = { 0,0 };
	transform = target;
}

void Movement::Update(float DeltaTime) 
{
	prevRelativeLocation = transform->GetRelativeLocation(); 
	MathHelper::Vector2F Location = prevRelativeLocation;
	Location += velocity * DeltaTime; 
	transform->SetRelativeLocation(Location);
}

void Movement::PrevPosition(bool prevX, bool prevY)
{
	if (prevX) transform->relativeLocation.x = prevRelativeLocation.x;	
	if (prevY) transform->relativeLocation.y = prevRelativeLocation.y;
}



