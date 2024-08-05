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
		D2D1::Matrix3x2F::Rotation(relativeRotation, imageCenter) * //이미지의 중심을 알아야함.. 
		//이게 먼저.. 
		//그러니까 내가 원하는거는 하나의 클라이언트에서 개발할때는하나의 좌표계로 통일하고싶은데.. 그게 이미지의 중심이고 그럴려면.. 여기 트랜스폼에서 처리해야하는게 아닌가 싶은거지.. 
		//그걸 확인할 오브젝트까지 띄워보자 제일 쉬운건 성.. 
		//중심좌표를 띄울수있도록해봅시다. 
		//일단 UI 부터 띄워볼까? 
		//아 회전된 오브젝트는 그냥 중심에 돌고있었지?

		//근데 궁금한게.. 회전은 분명 좌표가 왜이렇게 되지?? 이거는 물어보자.. 
		//월드좌표의 중심이란게.. 
		D2D1::Matrix3x2F::Translation(relativeLocation.x, relativeLocation.y);//역행렬에서.. 
	if (parentScene != nullptr)
		worldTransform = relativeTransform * parentScene->worldTransform;
	else
		worldTransform = relativeTransform;
}


void Transform::SetRelativeRotation(float Rotation)
{
	relativeRotation = Rotation;
	relativeRotation = fmodf(relativeRotation, 360.0f);
}

void Transform::AddRelativeRotation(float Rotation)
{
	relativeRotation += Rotation;
	relativeRotation = fmodf(relativeRotation, 360.0f);
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



