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

void Movement::PrevPosition(bool prevX, bool prevY) //트랜스폼에서 처리할까?
{
	if (prevX) transform->SetRelativeLocation({ prevRelativeLocation.x, transform->GetRelativeLocation().y });
	if (prevY)  transform->SetRelativeLocation({ transform->GetRelativeLocation().x, prevRelativeLocation.y });
}



