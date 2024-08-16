#pragma once
#include "Component.h"


class Transform : public Component
{
private :
	
	float	relativeRotation = 0; // ��� ȸ��
public:
	Transform();
	virtual ~Transform();
	Transform* parentScene = nullptr;		// �θ� Scene ������Ʈ
	std::vector<Transform*>  childScene;	// �ڽ� Scene ������Ʈ	
	D2D1_POINT_2F imageCenter = { 0,0 };	// ��� ��ġ 
	D2D_MATRIX_3X2_F	 relativeTransform; // ��� ���� ��ȯ						 
	D2D_MATRIX_3X2_F	 worldTransform;    // �θ���� �ݿ��� ���� ��ȯ
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
	MathHelper::Vector2F& GetRelativeLocation() { return relativeLocation; }
	MathHelper::Vector2F& GetRelativeScale() { return relativeScale; }; //�̰� �����γѰܼ� �������ؾ��ҵ� ��Ʈ��������
	MathHelper::Vector2F GetWorldScale();

	MathHelper::Vector2F relativeScale = { 1,1 };	// ��� ũ�� //��Ʈ���� �ҷ��� ���� �����ؾ���.. 
	MathHelper::Vector2F relativeLocation = { 0,0 }; // ��� ��ġ 
	std::wstring ShowPos();
};
