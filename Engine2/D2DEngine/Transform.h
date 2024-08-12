#pragma once
#include "Component.h"


class Transform : public Component
{
private :
	MathHelper::Vector2F relativeScale = { 1,1 };	// ��� ũ��
	MathHelper::Vector2F relativeLocation = { 0,0 }; // ��� ��ġ //�̰͵� �Ž� ���۷� ���ξȵǳ�?
	float	relativeRotation = 0; // ��� ȸ��
public:
	Transform();
	virtual ~Transform();
	Transform* parentScene = nullptr;		// �θ� Scene ������Ʈ
	std::vector<Transform*>  childScene;		// �ڽ� Scene ������Ʈ	
	D2D1_POINT_2F imageCenter = { 0,0 }; // ��� ��ġ //�̰͵� �Ž� ���۷� ���ξȵǳ�?  //���������鵵 ����ȭ�ұ�?
	D2D_MATRIX_3X2_F	 relativeTransform; // ��� ���� ��ȯ						 
	D2D_MATRIX_3X2_F	 worldTransform;    // �θ���� �ݿ��� ���� ��ȯ
	virtual void Update(float deltaTime) override;
	void SetParent(Transform* pParentScene) {
		pParentScene->childScene.push_back(this); //�θ� �����ص� �ڵ����� �ڽ����� ����
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

	//�θ���� ���� �ݿ��� ũ�Ⱚ���˼��ֳ�? 
	void SetRelativeScale(MathHelper::Vector2F scale); //get, set�� �˷������ϱ�.. 
	void SetRelativeRotation(float Rotation);
	void AddRelativeRotation(float Rotation);
	float GetRelativeRotation() { return relativeRotation; }

	void SetRelativeLocation(const MathHelper::Vector2F& Location);
	void AddRelativeLocation(float x, float y);
	const MathHelper::Vector2F& GetRelativeLocation() { return relativeLocation; }
	MathHelper::Vector2F GetWorldScale();

	std::wstring ShowPos();
};
