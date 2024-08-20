#include "pch.h"
#include "BorderEffect.h"
#include "D2DRenderer.h"

#include <wrl/client.h>
using namespace Microsoft::WRL;

BorderEffect::BorderEffect(ID2D1Bitmap* _Bitmap)
{
	D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1ChromaKey, &DefaultEffect); 
	// ũ�θ�Ű ������ �÷� ���ϱ� ���� CLSID_D2D1ColorMatrix
	D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &colorMatrixEffect);
	colorMatrixEffect->SetInput(0, _Bitmap);
	colorMatrixEffect->SetValue(D2D1_COLORMATRIX_PROP_CLAMP_OUTPUT, TRUE);
	// �ܰ��� ���ϱ�
	ComPtr<ID2D1Effect> edgeDetectionEffect;
	D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1EdgeDetection, &edgeDetectionEffect);
	edgeDetectionEffect->SetInput(0, _Bitmap);
	edgeDetectionEffect->SetValue(D2D1_EDGEDETECTION_PROP_STRENGTH, 1.0);
	edgeDetectionEffect->SetInputEffect(0, colorMatrixEffect);

	DefaultEffect->SetInput(0, _Bitmap);
	DefaultEffect->SetInputEffect(0, edgeDetectionEffect.Get());
}

BorderEffect::~BorderEffect()
{
	if (DefaultEffect)
	{
		DefaultEffect->Release();
		DefaultEffect = nullptr;
	}

	if (colorMatrixEffect)
	{
		colorMatrixEffect->Release();
		colorMatrixEffect = nullptr;
	}
}

void BorderEffect::EffectUpdate(float deltaTime)
{
	DefaultEffect->SetValue(D2D1_CHROMAKEY_PROP_COLOR, color);
	DefaultEffect->SetValue(D2D1_CHROMAKEY_PROP_TOLERANCE, 0.1f);
	DefaultEffect->SetValue(D2D1_CHROMAKEY_PROP_INVERT_ALPHA, false);
	DefaultEffect->SetValue(D2D1_CHROMAKEY_PROP_FEATHER, false);

	colorMatrixEffect->SetValue(D2D1_COLORMATRIX_PROP_COLOR_MATRIX, matrix);
}

// D2D1_CHROMAKEY_PROP_COLOR
// - �����ϰ� ��ȯ�� ���� �����մϴ�.
// - ���� ������ D2D1::ColorF Ȥ�� D2D1::Vector4F�Դϴ�.�⺻���� ������(0, 0, 0, 0) �Դϴ�.

// D2D1_CHROMAKEY_PROP_TOLERANCE
// - PROP_COLOR�� ������ ���� ���� ��� ������ �����մϴ�.
// - ���� ��� ������ 0.0 - 1.0�Դϴ�.�⺻���� 0.1�Դϴ�.

// D2D1_CHROMAKEY_PROP_INVERT_ALPHA
// - ���� �� ���� �����Դϴ�.
// - bool������ ������ �� �ֽ��ϴ�.�⺻���� false�Դϴ�.
 
// D2D1_CHROMAKEY_PROP_FEATHER
// - ��� �����ڸ��� �ε巴�� ó�������� �����Դϴ�.
// - bool������ ������ �� �ֽ��ϴ�.�⺻���� false�Դϴ�.