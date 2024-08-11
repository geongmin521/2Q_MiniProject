#pragma once
#include "SingletonBase.h"


class D2DEffect : public SingletonBase<D2DEffect>
{
private:
	std::unordered_map<std::wstring, ID2D1Effect*> Effects;

public:
	~D2DEffect();
	ID2D1Effect* FindEffect(const std::wstring& keyName);

public: // Ʈ������ ���� ����
	void Create2DAffineTransform(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, D2D1_MATRIX_3X2_F* matrix);
	void CreateEdgeEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap);

public: // ����Ʈ ����
	void CreateGaussianBlurEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, const float blurVal); // �帮�� ���鶧
	void CreateColorMatrixEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, D2D1_MATRIX_5X4_F _ColorMatrix); // ��Ʈ�ʿ� �������Ͽ� ���� ������
	void CreateBlendEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, ID2D1Bitmap* _BitmapTwo); // ��Ʈ�� ���� �� ��ġ�ų� �����Ҷ�
	void CreateMorphologyEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, int val); //  ������ ȿ�� https://learn.microsoft.com/ko-kr/windows/win32/direct2d/morphology

public: // �� ȿ��
	void Create2DLightEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap);

	void CreateSpecularEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap);
	void CreateDistanSpecularEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap);
	void CreatePointSpecularEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap);


};

// ���� 
// �ش� ������Ʈ���� ����ϰ� ���� ����Ʈ�� �����Ѵ�
// D2DEffect::GetInstance()->CreateGaussianBlurEffect(L"test", GetComponent<Animation>()->bitmap, 10.f);
// Render���� D2DRenderer::GetInstance()->DeviceContext->DrawImage(D2DEffect::GetInstance()->FindEffect(L"test"));
// D2DRenderer::GetInstance()->DeviceContext->DrawImage�� ���ؼ� ������ �ؾ� �Ѵ�. DrawImage���� ����Ʈ ������ ������
// FindEffect�� �̿��ؼ� ���� ���� ����Ʈ�� ã�Ƽ� ����ϸ� �ȴ�.