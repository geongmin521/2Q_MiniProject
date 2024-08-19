#pragma once
#include "SingletonBase.h"

class IEffect;
class Transform;
class D2DEffectManager : public SingletonBase<D2DEffectManager>
{
private:
	std::unordered_map<std::wstring, IEffect*> Effects;


public:
	D2DEffectManager();
	~D2DEffectManager();

	ID2D1Effect* FindEffect(const std::wstring& keyName); // 용도 IEffect안에 있는 DefaultEffect에 접근하기 위해
	template<typename T>
	T* FindIEffect(const std::wstring& keyName);  // 용도 IEffect 접근용

	void Update(float deltaTime);  
	void Render(ID2D1RenderTarget* pRenderTarget) {} // 보류 사항

public: // 트랜스폼 관련 적용
//	void CreateEdgeEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap);

public: // 이펙트 생성
	void CreateGaussianBlurEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, const float blurVal); // 흐리게 만들때
	void CreateColorMatrixEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, D2D1_MATRIX_5X4_F _ColorMatrix); // 비트맵에 색정렬하여 색을 넣을때
	void CreateBlendEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, ID2D1Bitmap* _BitmapTwo); // 비트맵 끼리 색 합치거나 구분할때
	void CreateCrossFadeEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, ID2D1Bitmap* _BitmapTwo); // 페이드맵
	void CreateMorphologyEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, int val); //  깨지는 효과 https://learn.microsoft.com/ko-kr/windows/win32/direct2d/morphology
	void CreateBorderEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap);

public: // 빛 효과
	void CreatePointSpecularEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, Transform* _Transform);
};

template<typename T>
T* D2DEffectManager::FindIEffect(const std::wstring& keyName)
{
    auto it = Effects.find(keyName);

    if (it != Effects.end())
    {
        T* effect = dynamic_cast<T*>(it->second);
        if (effect)
        {
            return effect;
        }
    }
    return nullptr;
}
