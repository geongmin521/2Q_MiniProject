#include "pch.h"
#include "Transform.h"

Transform::Transform()
{
	relativeTransform = worldTransform = D2D1::Matrix3x2F::Identity();
}

Transform::~Transform()
{

}

void Transform::Update(float deltaTime) //나는 모든 오브젝트의 중심이.. 이미지의중앙이었으면 좋겠단 말이야.. 
{
	relativeTransform = D2D1::Matrix3x2F::Scale(D2D1::SizeF(relativeScale.x, relativeScale.y)) *
		D2D1::Matrix3x2F::Rotation(relativeRotation, imageCenter) * 
		D2D1::Matrix3x2F::Translation(relativeLocation.x, relativeLocation.y);
	if (parentScene != nullptr)
		worldTransform = relativeTransform * parentScene->worldTransform;
	else
		worldTransform = relativeTransform;
}

MathHelper::Vector2F Transform::GetWorldScale() { //월드행렬에서 순수하게 사이즈만 출력한다?
	// 행렬에서 스케일 값을 추출합니다.
	MathHelper::Vector2F scale;
	scale.x = sqrt(worldTransform.m11 * worldTransform.m11 + worldTransform.m21 * worldTransform.m21);
	scale.y = sqrt(worldTransform.m12 * worldTransform.m12 + worldTransform.m22 * worldTransform.m22);
	return scale;
}

void Transform::SetRelativeScale(MathHelper::Vector2F scale)
{
	relativeScale = scale;
	Update(1); //본인의 값이 변경되었을때.. 특히 스타트에서?
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


void Transform::SetRelativeLocation(const MathHelper::Vector2F& Location) //누군가 상대좌표를 이동시키면 즉시 월드 좌표에 적용될수있게하기
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
	
	return L"로컬좌표: " + std::to_wstring(relativeLocation.x) + L"  " + std::to_wstring(relativeLocation.y)
		+  L"절대좌표: " + std::to_wstring(GetWorldLocation().x) + L"  " + std::to_wstring(GetWorldLocation().y);
}



