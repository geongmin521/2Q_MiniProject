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

	ID2D1Effect* FindEffect(const std::wstring& keyName); // �뵵 IEffect�ȿ� �ִ� DefaultEffect�� �����ϱ� ����
	template<typename T>
	T* FindIEffect(const std::wstring& keyName);  // �뵵 IEffect ���ٿ�

	void Update(float deltaTime);  
	void Render(ID2D1RenderTarget* pRenderTarget); // ���� ����

public: // Ʈ������ ���� ����
//	void Create2DAffineTransform(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, D2D1_MATRIX_3X2_F* matrix);
//	void CreateEdgeEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap);

public: // ����Ʈ ����
	void CreateGaussianBlurEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, const float blurVal); // �帮�� ���鶧
	void CreateColorMatrixEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, D2D1_MATRIX_5X4_F _ColorMatrix); // ��Ʈ�ʿ� �������Ͽ� ���� ������
	void CreateBlendEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, ID2D1Bitmap* _BitmapTwo); // ��Ʈ�� ���� �� ��ġ�ų� �����Ҷ�
//	void CreateCrossFadeEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, ID2D1Bitmap* _BitmapTwo); // ���̵��
//	void CreateMorphologyEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, int val); //  ������ ȿ�� https://learn.microsoft.com/ko-kr/windows/win32/direct2d/morphology

public: // �� ȿ��
//	void CreateDistantDiffuseEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap);

//	void CreateSpecularEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, Transform* LightTransform);
//	void CreateDistanSpecularEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap);
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
