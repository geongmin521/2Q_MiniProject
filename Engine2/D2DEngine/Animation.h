
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
	// 공유하는 애니메이션 정보	
	AnimationAsset* animationAsset = nullptr;  // 공유하는 애니메이션 정보

	// 인스턴스마다 다른 애니메이션 정보
	ANIMATION_INFO* animationInfo = nullptr;	// 현재 애니메이션 프레임 정보
	std::wstring animationAssetFilePath;    // 애니메이션 정보 파일 이
	float frameTime = 0.0f;	// 프레임 진행시간
	int frameIndexCurr = -1;	// 현재 프레임 인덱스
	int frameIndexPrev = -1;	// 이전 프레임 인덱스
	int animationIndex = -1;	// 현재 애니메이션 인덱스
	D2D1_RECT_F srcRect;		// D2D1Bitmap의 Source 영역
	
	bool IsEnd() { return  animationEnd; }
	void LoadAnimationAsset(const std::wstring strFilePath);
	virtual void Update(float fTimeElapsed) override;
	virtual void Render(ID2D1RenderTarget* pRenderTarget) override;
	void SetAnimation(int index, bool mirror);
	void Reverse(); 
};

