#pragma once
#include "SingletonBase.h"


class D2DEffect : public SingletonBase<D2DEffect>
{
private:
	std::unordered_map<std::wstring, ID2D1Effect*> Effects;

public:
	~D2DEffect();
	ID2D1Effect* FindEffect(const std::wstring& keyName);

public: // 트랜스폼 관련 적용
	void Create2DAffineTransform(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, D2D1_MATRIX_3X2_F* matrix);
	void CreateEdgeEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap);

public: // 이펙트 생성
	void CreateGaussianBlurEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, const float blurVal); // 흐리게 만들때
	void CreateColorMatrixEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, D2D1_MATRIX_5X4_F _ColorMatrix); // 비트맵에 색정렬하여 색을 넣을때
	void CreateBlendEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, ID2D1Bitmap* _BitmapTwo); // 비트맵 끼리 색 합치거나 구분할때
	void CreateMorphologyEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, int val); //  깨지는 효과 https://learn.microsoft.com/ko-kr/windows/win32/direct2d/morphology

public: // 빛 효과
	void Create2DLightEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap);

	void CreateSpecularEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap);
	void CreateDistanSpecularEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap);
	void CreatePointSpecularEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap);


};

// 사용법 
// 해당 오브젝트에서 사용하고 싶은 이펙트를 생성한다
// D2DEffect::GetInstance()->CreateGaussianBlurEffect(L"test", GetComponent<Animation>()->bitmap, 10.f);
// Render에서 D2DRenderer::GetInstance()->DeviceContext->DrawImage(D2DEffect::GetInstance()->FindEffect(L"test"));
// D2DRenderer::GetInstance()->DeviceContext->DrawImage를 통해서 랜더를 해야 한다. DrawImage에서 이펙트 렌더를 지원함
// FindEffect를 이용해서 내가 만든 이펙트를 찾아서 사용하면 된다.