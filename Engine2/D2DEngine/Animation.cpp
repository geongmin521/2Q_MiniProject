#include "pch.h"
#include "Animation.h"
#include "AnimationAsset.h"
#include "D2DRenderer.h"
#include "ResourceManager.h"
#include "D2DEffect.h"

Animation::Animation(std::wstring bitmap, std::wstring animation): Renderer(bitmap) 
{
	LoadAnimationAsset(animation); 
	SetAnimation(0, false); 
}

Animation::~Animation()
{
	if (animationAsset)
	{
		ResourceManager::Instance->ReleaseAnimationAsset(animationAssetFilePath);
		animationAsset = nullptr;
	}
}

void Animation::LoadAnimationAsset(const std::wstring strFilePath)
{
	animationAssetFilePath = strFilePath;
	ResourceManager::Instance->CreateAnimationAsset(strFilePath, &animationAsset);
}



void Animation::Update(float fTimeElapsed)	
{
	__super::Update(fTimeElapsed);

	assert(animationAsset != nullptr);

	if (animationInfo == nullptr)
		return;
	if (isLoop == false && animationEnd == true) 
		return;
	const FRAME_INFO& Frame = animationInfo->Frames[frameIndexCurr];
	size_t MaxFrameCount = animationInfo->Frames.size();

	frameTime += fTimeElapsed;

	if (isLoop == false
		&& frameIndexCurr == (MaxFrameCount - 1)   // 현재 프레임이 마지막 프레임이라면
		&& frameTime >= Frame.Duration)	// 현재 프레임의 시간이 Duration보다 크다면
	{
		animationEnd = true;
	}

	if (Frame.Duration < frameTime)
	{
		frameIndexCurr++;
		frameTime = 0;
		if (animationInfo->Frames.size() <= frameIndexCurr)
		{
			frameIndexCurr = 0; 
		}
	}

	if (mirror) //x 축 스케일은 좌우 반전 , Translation 은 출력할 이미지의 원점 정보
	{
		imageTransform = D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, D2D1::Point2F(Frame.Center.x, Frame.Center.y)) *
			D2D1::Matrix3x2F::Translation(-Frame.Center.x, -Frame.Center.y);
	}
	else
	{
		imageTransform = D2D1::Matrix3x2F::Scale(1.0f, 1.0f, D2D1::Point2F(Frame.Center.x, Frame.Center.y)) *
			D2D1::Matrix3x2F::Translation(-Frame.Center.x, -Frame.Center.y);
	}
	srcRect = Frame.Source;
	DstRect = { 0,0,srcRect.right - srcRect.left,srcRect.bottom - srcRect.top };

//	static float testtimer = 0;
//	testtimer += 10 * fTimeElapsed;
//
//	if (testtimer < 3)
//	{
//		Testbool = false;
//	}
//	else if (testtimer > 3 && testtimer < 6)
//	{
//		Testbool = true;
//	
//	}
//	else
//	{
//		testtimer = 0;
//	}
}

void Animation::Render(ID2D1RenderTarget* pRenderTarget,float Alpha)
{
	if (animationInfo == nullptr)
		return;
	__super::Render(pRenderTarget);


	if (Testbool == true)
	{	
		pRenderTarget->DrawBitmap(bitmap, DstRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, srcRect);
	}
	else
	{
//		// Test 몬스터 피격효과 
//		D2D1_MATRIX_5X4_F redEmphasis =
//		{
//		0.5f, 0.0f, 0.0f, 1.0f, 0.9f,
//		0.0f, 0.3f, 0.0f, 0.0f, 0.0f,
//		0.0f, 0.0f, 0.2f, 0.0f, 0.0f,
//		0.0f, 0.0f, 0.0f, 0.0f, 0.0f
//		};
//
//		D2DRenderer::GetInstance()->CreateColorMatrixEffect(bitmap, redEmphasis);
//		D2DEffect::GetInstance()->CreateEdgeEffect(L"Edge", bitmap);
//		D2DRenderer::GetInstance()->DeviceContext->DrawImage(D2DEffect::GetInstance()->FindEffect(L"Edge"), {0,0}, srcRect);
	}

	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void Animation::SetAnimation(int index, bool mirror)
{
	assert(animationAsset != nullptr);

	ANIMATION_INFO* pFound = animationAsset->GetAnimationInfo(index);
	if (pFound == nullptr)
		return;
	isLoop = true;
	animationInfo = pFound;
	this->mirror = mirror;
	frameIndexCurr = 0;
	frameIndexPrev = 0;
	frameTime = 0.0f;
	animationEnd = false;
}

void Animation::Reverse()
{
	mirror = !mirror;
}
