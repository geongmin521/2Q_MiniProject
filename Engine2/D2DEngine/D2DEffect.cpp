#include "pch.h"
#include "D2DEffect.h"
#include "D2DRenderer.h"

D2DEffect::~D2DEffect()
{
	for (auto& pair : Effects) 
	{
		if (pair.second) 
		{
			pair.second->Release();  
			pair.second = nullptr;   
		}
	}
	Effects.clear();  
}

ID2D1Effect* D2DEffect::FindEffect(const std::wstring& keyName)
{
	// unordered_map의 find 함수를 사용하여 키 검색
	auto it = Effects.find(keyName);

	if (it != Effects.end())
	{
		return it->second;
	}
	return nullptr;
}

void D2DEffect::CreateGaussianBlurEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, const float blurVal)
{
	if (Effects.find(_KeyName) != Effects.end()) { return; } // 예외처리 해당 키를 가진게 있으면 생성을 하지 않음

	ID2D1Effect* blurEffect = nullptr;
	if (nullptr == D2DRenderer::GetInstance()->DeviceContext) { return; }

	D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1GaussianBlur, &blurEffect);
	if (blurEffect == nullptr) { return; }

	blurEffect->SetInput(0, _Bitmap); //이미지 인덱스 https://learn.microsoft.com/ko-kr/windows/win32/api/d2d1_1/nf-d2d1_1-id2d1effect-setinput
	blurEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, blurVal);
	Effects.insert(std::make_pair(_KeyName, blurEffect));
//	GaussianBlurEffect->GetOutput(&D2D1Image); // 렌더링 효과를 전달 https://learn.microsoft.com/ko-kr/windows/win32/api/d2d1_1/nf-d2d1_1-id2d1effect-getoutput
}

void D2DEffect::CreateColorMatrixEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, D2D1_MATRIX_5X4_F _ColorMatrix)
{
	if (Effects.find(_KeyName) != Effects.end()) { return; } // 예외처리 해당 키를 가진게 있으면 생성을 하지 않음

	ID2D1Effect* colorMatrixEffect = nullptr;
	D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &colorMatrixEffect);
	if (colorMatrixEffect == nullptr) { return; }

	colorMatrixEffect->SetInput(0, _Bitmap);
	colorMatrixEffect->SetValue(D2D1_COLORMATRIX_PROP_COLOR_MATRIX, _ColorMatrix);
	Effects.insert(std::make_pair(_KeyName,colorMatrixEffect));
}
// | Red Multiplier | Green Multiplier | Blue Multiplier | Alpha Multiplier | Red Offset   |
// |-------------------- | -------------------- | -------------------- | -------------------- | --------------|
// | Green Multiplier | Red Multiplier | Blue Multiplier | Alpha Multiplier | Green Offset |
// | Blue Multiplier | Green Multiplier | Red Multiplier | Alpha Multiplier | Blue Offset  |
// | Alpha Multiplier | Green Multiplier | Blue Multiplier | Red Multiplier | Alpha Offset |

void D2DEffect::Create2DLightEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap)
{
	if (Effects.find(_KeyName) != Effects.end()) { return; }
	ID2D1Effect* distantDiffuseEffect = nullptr;
	D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1DistantDiffuse, &distantDiffuseEffect);

	FLOAT azimuth = 0.0f;// 예제 값
	//시계 반대 방향의 X축을 기준으로 XY 평면의 광원 방향 각도입니다. 단위는 도이며 0~360도 사이여야 합니다.
	distantDiffuseEffect->SetValue(D2D1_DISTANTDIFFUSE_PROP_AZIMUTH, azimuth);

	// 광원의 고도 설정 (0~360도)
	FLOAT elevation = 90.0f;  // 예제 값
	//카운터 클록의 Y축을 기준으로 YZ 평면에서 광원의 방향 각도를 지정합니다. 단위는 도이며 0~360도 사이여야 합니다.
	distantDiffuseEffect->SetValue(D2D1_DISTANTDIFFUSE_PROP_ELEVATION, elevation);

	// 확산 상수 설정 (0~10,000) //0값이면 검은색으로 보임
	FLOAT diffuseConstant = 6.f; //6이 연노랑 원본과 제일 유사했음.
	//들어오는 광원 양에 대한 확산 반사 비율입니다. 이 속성은 0에서 10,000 사이여야 하며 단위가 없습니다.
	distantDiffuseEffect->SetValue(D2D1_DISTANTDIFFUSE_PROP_DIFFUSE_CONSTANT, diffuseConstant);

	// 표면 스케일 설정 (0~10,000)
	FLOAT surfaceScale = 0.0f;
    //Z 방향의 배율 인수입니다. 표면 눈금은 단위가 없으며 0에서 10,000 사이여야 합니다.
	distantDiffuseEffect->SetValue(D2D1_DISTANTDIFFUSE_PROP_SURFACE_SCALE, surfaceScale);
 
	// 조명 색상 설정
	D2D1_VECTOR_3F lightColor = D2D1::Vector3F(0.5f, 0.5f, 0.1f); // 약간의 노란색
    //들어오는 조명의 색입니다. 이 속성은 D2D1_VECTOR_3F (R, G, B)로 노출되며 LR, LG, LB를 계산하는 데 사용됩니다.
	distantDiffuseEffect->SetValue(D2D1_DISTANTDIFFUSE_PROP_COLOR, lightColor);

//	// 커널 유닛 길이 설정
	D2D1_VECTOR_2F kernelUnitLength = D2D1::Vector2F(1.0f, 0.5f);
 	//X 및 Y 방향으로 표면 보통을 생성하는 데 사용되는 Sobel 커널의 요소 크기입니다. 
    //이 속성은 Sobel 그라데이션의 dx 및 dy 값에 매핑됩니다. 
    //이 속성은 D2D1_VECTOR_2F(커널 단위 길이 X, 커널 단위 길이 Y)이며(디바이스 독립적 픽셀(DIP)/커널 단위)에 정의되어 있습니다. 
    //이 효과는 쌍선형 보간을 사용하여 커널 요소의 크기와 일치하도록 비트맵의 크기를 조정합니다.
	distantDiffuseEffect->SetValue(D2D1_DISTANTDIFFUSE_PROP_KERNEL_UNIT_LENGTH, kernelUnitLength);

//	// 크기 조정 모드 설정 https://learn.microsoft.com/ko-kr/windows/win32/api/d2d1effects/ne-d2d1effects-d2d1_distantdiffuse_scale_mode
	D2D1_DISTANTDIFFUSE_SCALE_MODE scaleMode = D2D1_DISTANTDIFFUSE_SCALE_MODE_LINEAR;
	distantDiffuseEffect->SetValue(D2D1_DISTANTDIFFUSE_PROP_SCALE_MODE, scaleMode);

	distantDiffuseEffect->SetInput(0, _Bitmap);

	Effects.insert(std::make_pair(_KeyName, distantDiffuseEffect));
}

void D2DEffect::CreateBlendEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, ID2D1Bitmap* _BitmapTwo)
{
	if (Effects.find(_KeyName) != Effects.end()) { return; }
	ID2D1Effect* blendEffect = nullptr;
	D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1Blend, &blendEffect);

	blendEffect->SetInput(0, _Bitmap);
	blendEffect->SetInput(1, _BitmapTwo);
	blendEffect->SetValue(D2D1_BLEND_PROP_MODE, D2D1_BLEND_MODE_EXCLUSION);
	Effects.insert(std::make_pair(_KeyName, blendEffect));
}

void D2DEffect::CreateMorphologyEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap ,int val)
{
	if (Effects.find(_KeyName) != Effects.end()) { return; }
	ID2D1Effect* morphologyEffect;
	D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1Morphology, &morphologyEffect);
	morphologyEffect->SetInput(0, _Bitmap);

	morphologyEffect->SetValue(D2D1_MORPHOLOGY_PROP_MODE, D2D1_MORPHOLOGY_MODE_ERODE);
	morphologyEffect->SetValue(D2D1_MORPHOLOGY_PROP_WIDTH, val);
	Effects.insert(std::make_pair(_KeyName, morphologyEffect));
}
