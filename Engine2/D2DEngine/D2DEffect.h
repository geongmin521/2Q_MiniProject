#pragma once
#include "SingletonBase.h"

class D2DEffect : public SingletonBase<D2DEffect>
{
private:
	std::unordered_map<std::wstring, ID2D1Effect*> Effects;

public:
	~D2DEffect();
	ID2D1Effect* FindEffect(const std::wstring& keyName);

public: // 이펙트 생성
	void CreateGaussianBlurEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, const float blurVal);
	void CreateColorMatrixEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, D2D1_MATRIX_5X4_F _ColorMatrix);
	void Create2DLightEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap);
	void CreateBlendEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, ID2D1Bitmap* _BitmapTwo);
	void CreateMorphologyEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, int val); // https://learn.microsoft.com/ko-kr/windows/win32/direct2d/morphology
};

// 사용법 
// 해당 오브젝트에서 사용하고 싶은 이펙트를 생성한다
// D2DEffect::GetInstance()->CreateGaussianBlurEffect(L"test", GetComponent<Animation>()->bitmap, 10.f);
// Render에서 D2DRenderer::GetInstance()->DeviceContext->DrawImage(D2DEffect::GetInstance()->FindEffect(L"test"));
// D2DRenderer::GetInstance()->DeviceContext->DrawImage를 통해서 랜더를 해야 한다. DrawImage에서 이펙트 렌더를 지원함
// FindEffect를 이용해서 내가 만든 이펙트를 찾아서 사용하면 된다.