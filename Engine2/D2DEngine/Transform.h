#pragma once
#include "Component.h"


class Transform : public Component
{
private :
	MathHelper::Vector2F relativeScale = { 1,1 };	// 상대 크기
	MathHelper::Vector2F relativeLocation = { 0,0 }; // 상대 위치 
	float	relativeRotation = 0; // 상대 회전
public:
	Transform();
	virtual ~Transform();
	Transform* parentScene = nullptr;		// 부모 Scene 컴포넌트
	std::vector<Transform*>  childScene;	// 자식 Scene 컴포넌트	
	D2D1_POINT_2F imageCenter = { 0,0 };	// 상대 위치 
	D2D_MATRIX_3X2_F	 relativeTransform; // 상대 복합 변환						 
	D2D_MATRIX_3X2_F	 worldTransform;    // 부모까지 반영된 최종 변환
	virtual void Update(float deltaTime) override;
	void SetParent(Transform* pParentScene) {
		pParentScene->childScene.push_back(this); 
		parentScene = pParentScene;
	}
	void SetImageCenter(D2D1_POINT_2F center) { this->imageCenter = center; }

	MathHelper::Vector2F GetWorldLocation()
	{
		D2D1_VECTOR_2F out;
		out.x = worldTransform._31;
		out.y = worldTransform._32;
		return out;
	}

	void SetRelativeScale(MathHelper::Vector2F scale); 
	void SetRelativeRotation(float Rotation);
	void AddRelativeRotation(float Rotation);
	float GetRelativeRotation() { return relativeRotation; }
	void SetRelativeLocation(const MathHelper::Vector2F& Location);
	void AddRelativeLocation(float x, float y);
	const MathHelper::Vector2F& GetRelativeLocation() { return relativeLocation; }
	MathHelper::Vector2F GetWorldScale();

	std::wstring ShowPos();
};
