#include "pch.h"
#include "BorderEffect.h"
#include "D2DRenderer.h"

#include <wrl/client.h>
using namespace Microsoft::WRL;

BorderEffect::BorderEffect(ID2D1Bitmap* _Bitmap)
{
	D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1ChromaKey, &DefaultEffect); 
	// 크로마키 적용할 컬러 정하기 위해 CLSID_D2D1ColorMatrix
	D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &colorMatrixEffect);
	colorMatrixEffect->SetInput(0, _Bitmap);
	colorMatrixEffect->SetValue(D2D1_COLORMATRIX_PROP_CLAMP_OUTPUT, TRUE);
	// 외각선 구하기
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
// - 투명하게 변환할 색을 지정합니다.
// - 값의 형식은 D2D1::ColorF 혹은 D2D1::Vector4F입니다.기본값은 검정색(0, 0, 0, 0) 입니다.

// D2D1_CHROMAKEY_PROP_TOLERANCE
// - PROP_COLOR로 지정한 색에 대한 허용 오차를 지정합니다.
// - 값의 허용 범위는 0.0 - 1.0입니다.기본값은 0.1입니다.

// D2D1_CHROMAKEY_PROP_INVERT_ALPHA
// - 알파 값 반전 여부입니다.
// - bool값으로 지정할 수 있습니다.기본값은 false입니다.
 
// D2D1_CHROMAKEY_PROP_FEATHER
// - 출력 가장자리를 부드럽게 처리할지의 여부입니다.
// - bool값으로 지정할 수 있습니다.기본값은 false입니다.