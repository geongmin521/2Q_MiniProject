#pragma once
#include "Component.h"


class Transform : public Component
{
private :
	
public:
	Transform();
	virtual ~Transform();
	Transform* parentScene = nullptr;		// 부모 Scene 컴포넌트	
	MathHelper::Vector2F relativeScale = { 1,1 };	// 상대 크기
	MathHelper::Vector2F relativeLocation = { 0,0 }; // 상대 위치 //이것도 매스 헬퍼로 매핑안되나? 
	D2D1_POINT_2F imageCenter = { 0,0 }; // 상대 위치 //이것도 매스 헬퍼로 매핑안되나? 
	D2D_MATRIX_3X2_F	 relativeTransform; // 상대 복합 변환						 
	D2D_MATRIX_3X2_F	 worldTransform;    // 부모까지 반영된 최종 변환
	float	relativeRotation = 0; // 상대 회전
	// RelativeTransform과 	worldTransform을 계산한다.
	virtual void Update(float deltaTime) override;
	void SetParent(Transform* pParentScene) { parentScene = pParentScene; }
	void SetImageCenter(D2D1_POINT_2F center) { this->imageCenter = center; }

	MathHelper::Vector2F GetWorldLocation()
	{
		D2D1_VECTOR_2F out;
		out.x = worldTransform._31;
		out.y = worldTransform._32;
		return out;
	}

	void SetRelativeRotation(float Rotation);
	void AddRelativeRotation(float Rotation);
	float GetRelativeRotation() { return relativeRotation; }

	void SetRelativeLocation(const MathHelper::Vector2F& Location);
	void AddRelativeLocation(float x, float y);
	const MathHelper::Vector2F& GetRelativeLocation() { return relativeLocation; }

	std::wstring ShowPos();
};
