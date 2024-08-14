#include "pch.h"
#include "Transform.h"
#include "GameObject.h"
#include "Bitmap.h"
#include "Animation.h"

Transform::Transform()
{
	relativeTransform = worldTransform = D2D1::Matrix3x2F::Identity();
}

Transform::~Transform()
{

}

void Transform::Update(float deltaTime) 
{
	relativeTransform = D2D1::Matrix3x2F::Scale(D2D1::SizeF(relativeScale.x, relativeScale.y)) *
		D2D1::Matrix3x2F::Rotation(relativeRotation) * 
		D2D1::Matrix3x2F::Translation(relativeLocation.x, relativeLocation.y);
	if (parentScene != nullptr)
		worldTransform = relativeTransform * parentScene->worldTransform;
	else
		worldTransform = relativeTransform;
}

MathHelper::Vector2F Transform::GetWorldScale() {
	MathHelper::Vector2F scale;
	scale.x = sqrt(worldTransform.m11 * worldTransform.m11 + worldTransform.m21 * worldTransform.m21);
	scale.y = sqrt(worldTransform.m12 * worldTransform.m12 + worldTransform.m22 * worldTransform.m22);
	return scale;
}

void Transform::SetRelativeScale(MathHelper::Vector2F scale)
{
	relativeScale = scale;	
	Update(1); 
}

void Transform::SetRelativeRotation(float Rotation)
{
	relativeRotation = Rotation;
	relativeRotation = fmodf(relativeRotation, 360.0f);
	Update(1);
}

void Transform::AddRelativeRotation(float Rotation)
{
	relativeRotation += Rotation;
	relativeRotation = fmodf(relativeRotation, 360.0f);
	Update(1);
}


void Transform::SetRelativeLocation(const MathHelper::Vector2F& Location)
{
	relativeLocation = Location;
	Update(1);
}

void Transform::AddRelativeLocation(float x, float y)
{
	relativeLocation = { relativeLocation.x + x,relativeLocation.y + y };
}

std::wstring Transform::ShowPos()
{
	
	return L"·ÎÄÃÁÂÇ¥: " + std::to_wstring(relativeLocation.x) + L"  " + std::to_wstring(relativeLocation.y)
		+  L"Àý´ëÁÂÇ¥: " + std::to_wstring(GetWorldLocation().x) + L"  " + std::to_wstring(GetWorldLocation().y);
}



