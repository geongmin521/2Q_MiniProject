#pragma once
#include "SingletonBase.h"

class D2DEffect;
class Transform;
class D2DEffectManager : public SingletonBase<D2DEffectManager>
{
private:
	std::unordered_map<std::wstring, ID2D1Effect*> Effects; 

public:
	D2DEffectManager();
	~D2DEffectManager();
	ID2D1Effect* FindEffect(const std::wstring& keyName);

	void Update(float deltaTime);
	void Render(ID2D1RenderTarget* pRenderTarget);

public: // 트랜스폼 관련 적용
	void Create2DAffineTransform(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, D2D1_MATRIX_3X2_F* matrix);
	void CreateEdgeEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap);

public: // 이펙트 생성
	void CreateGaussianBlurEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, const float blurVal); // 흐리게 만들때
	void CreateColorMatrixEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, D2D1_MATRIX_5X4_F _ColorMatrix); // 비트맵에 색정렬하여 색을 넣을때
	void CreateBlendEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, ID2D1Bitmap* _BitmapTwo); // 비트맵 끼리 색 합치거나 구분할때
	void CreateMorphologyEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, int val); //  깨지는 효과 https://learn.microsoft.com/ko-kr/windows/win32/direct2d/morphology
	void CreateCrossFadeEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, ID2D1Bitmap* _BitmapTwo);

public: // 빛 효과
	void CreateDistantDiffuseEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap);

	void CreateSpecularEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, Transform* LightTransform);
	void CreateDistanSpecularEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap);
	void CreatePointSpecularEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap);
};

