
#pragma once
#include "Renderer.h"

class AnimationAsset;
struct ANIMATION_INFO;

class Animation :public Renderer
{
private:
	bool animationEnd;

public:
	Animation(std::wstring bitmap, std::wstring animation);
	virtual ~Animation();
	bool isLoop = true;
	// �����ϴ� �ִϸ��̼� ����	
	AnimationAsset* animationAsset = nullptr;  // �����ϴ� �ִϸ��̼� ����

	// �ν��Ͻ����� �ٸ� �ִϸ��̼� ����
	ANIMATION_INFO* animationInfo = nullptr;	// ���� �ִϸ��̼� ������ ����
	std::wstring animationAssetFilePath;    // �ִϸ��̼� ���� ���� ��
	float frameTime = 0.0f;		// ������ ����ð�
	int frameIndexCurr = -1;	// ���� ������ �ε���
	int frameIndexPrev = -1;	// ���� ������ �ε���
	int animationIndex = -1;	// ���� �ִϸ��̼� �ε���
	
	
	bool IsEnd() { return  animationEnd; }
	void LoadAnimationAsset(const std::wstring strFilePath);
	virtual void Update(float fTimeElapsed) override;
	virtual void Render(ID2D1RenderTarget* pRenderTarget,float Alpha = 1) override;
	void SetAnimation(int index, bool mirror, bool isloop = true);
	void Reverse(); 

	// ����Ʈ ���� ���ϱ� ���� �ϴ� �߰��� ��
	D2D1_POINT_2F CenterPos;
};

