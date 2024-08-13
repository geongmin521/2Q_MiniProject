#include "pch.h"
#include "D2DEffect.h"
#include "D2DRenderer.h"
#include <wrl.h>

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

void D2DEffect::Create2DAffineTransform(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, D2D1_MATRIX_3X2_F* matrix)
{
	if (Effects.find(_KeyName) != Effects.end()) { return; }
	ID2D1Effect * affineTransform;
	D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D12DAffineTransform, &affineTransform);
	affineTransform->SetInput(0, _Bitmap);
	affineTransform->SetValue(D2D1_2DAFFINETRANSFORM_PROP_TRANSFORM_MATRIX, matrix);
	Effects.insert(std::make_pair(_KeyName, affineTransform));
}

// https://learn.microsoft.com/ko-kr/windows/win32/api/d2d1effects_2/ne-d2d1effects_2-d2d1_edgedetection_prop
void D2DEffect::CreateEdgeEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap)
{
	if (Effects.find(_KeyName) != Effects.end()) { return; }
	ID2D1Effect* EdgeEffect;
	D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1EdgeDetection, &EdgeEffect);
	EdgeEffect->SetInput(0, _Bitmap);
	EdgeEffect->SetValue(D2D1_EDGEDETECTION_PROP_STRENGTH, 0.8);
	EdgeEffect->SetValue(D2D1_EDGEDETECTION_PROP_OVERLAY_EDGES, false);

	Effects.insert(std::make_pair(_KeyName, EdgeEffect));
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
// | Red Multiplier | Green Multiplier | Blue Multiplier | Alpha = 1 Multiplier | Red Offset   |
// |-------------------- | -------------------- | -------------------- | -------------------- | --------------|
// | Green Multiplier | Red Multiplier | Blue Multiplier | Alpha = 1 Multiplier | Green Offset |
// | Blue Multiplier | Green Multiplier | Red Multiplier | Alpha = 1 Multiplier | Blue Offset  |
// | Alpha = 1 Multiplier | Green Multiplier | Blue Multiplier | Red Multiplier | Alpha = 1 Offset |

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
	blendEffect->SetValue(D2D1_BLEND_PROP_MODE, D2D1_BLEND_MODE_LINEAR_LIGHT);
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
//D2D1_MATRIX_5X4_F redEmphasis =
//		{
//		0.5f, 0.0f, 0.0f, 1.0f, 0.9f,
//		0.0f, 0.3f, 0.0f, 0.0f, 0.0f,
//		0.0f, 0.0f, 0.2f, 0.0f, 0.0f,
//		0.0f, 0.0f, 0.0f, 0.0f, 0.0f
//		};



void D2DEffect::CreateSpecularEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap)
{
	if (Effects.find(_KeyName) != Effects.end()) { return; }
	ID2D1Effect* SpecularEffect;
	D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1SpotSpecular, &SpecularEffect);

	// 광원의 위치 설정 (x, y, z)
	D2D1_VECTOR_3F lightPosition = D2D1::Vector3F(0.0f, 0.0f, 500.0f); // 적절한 값으로 설정
	SpecularEffect->SetValue(D2D1_SPOTSPECULAR_PROP_LIGHT_POSITION, lightPosition);
	// 조명의 포커스 위치 설정
	D2D1_VECTOR_3F pointsAt = D2D1::Vector3F(0.0f, 0.0f, 0.0f); // 포커스 위치
	SpecularEffect->SetValue(D2D1_SPOTSPECULAR_PROP_POINTS_AT, pointsAt);
	// 포커스 설정 (0에서 200 사이)
	SpecularEffect->SetValue(D2D1_SPOTSPECULAR_PROP_FOCUS, 50.0f);
	// 제한 원뿔 각도 설정 (0~90도)
	SpecularEffect->SetValue(D2D1_SPOTSPECULAR_PROP_LIMITING_CONE_ANGLE, 45.0f);
	// 반사광 지수 설정 (1.0에서 128 사이)
	SpecularEffect->SetValue(D2D1_SPOTSPECULAR_PROP_SPECULAR_EXPONENT, 50.0f);
	// 반사 상수 설정 (0에서 10,000 사이)
	SpecularEffect->SetValue(D2D1_SPOTSPECULAR_PROP_SPECULAR_CONSTANT, 2.0f);
	// 표면 스케일 설정
	SpecularEffect->SetValue(D2D1_SPOTSPECULAR_PROP_SURFACE_SCALE, 1.0f);
	// 조명의 색상 설정
	D2D1_VECTOR_3F lightColor = D2D1::Vector3F(1.0f, 1.0f, 1.0f); // 백색 조명
	SpecularEffect->SetValue(D2D1_SPOTSPECULAR_PROP_COLOR, lightColor);

	SpecularEffect->SetInput(0, _Bitmap);
	Effects.insert(std::make_pair(_KeyName, SpecularEffect));
}

void D2DEffect::CreateDistanSpecularEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap)
{
	if (Effects.find(_KeyName) != Effects.end()) { return; }
	ID2D1Effect* DistantSpecularEffect;
	D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1DistantSpecular, &DistantSpecularEffect);
	DistantSpecularEffect->SetValue(D2D1_DISTANTSPECULAR_PROP_AZIMUTH, 180.0f);  // 방위각
	DistantSpecularEffect->SetValue(D2D1_DISTANTSPECULAR_PROP_ELEVATION, 90.0f); // 고도 (태양이 머리 위에서 비추는 효과)
	DistantSpecularEffect->SetValue(D2D1_DISTANTSPECULAR_PROP_SPECULAR_EXPONENT, 50.0f); // 반사 지수 (더 강한 반사)
	DistantSpecularEffect->SetValue(D2D1_DISTANTSPECULAR_PROP_SPECULAR_CONSTANT, 1.0f); // 반사 상수 (광원의 밝기 증가)
	DistantSpecularEffect->SetValue(D2D1_DISTANTSPECULAR_PROP_SURFACE_SCALE, 5.0f);    // 표면 스케일 (높이 증가)
	DistantSpecularEffect->SetValue(D2D1_DISTANTSPECULAR_PROP_COLOR, D2D1::Vector3F(1.0f, 0.95f, 0.8f)); // 조명 색상 (태양빛 색상)
	DistantSpecularEffect->SetValue(D2D1_DISTANTSPECULAR_PROP_KERNEL_UNIT_LENGTH, D2D1::Vector2F(1.0f, 1.0f)); // 커널 단위 길이
	DistantSpecularEffect->SetValue(D2D1_DISTANTSPECULAR_PROP_SCALE_MODE, D2D1_DISTANTSPECULAR_SCALE_MODE_HIGH_QUALITY_CUBIC); // 스케일 모드 (고품질)
	
	DistantSpecularEffect->SetInput(0, _Bitmap);
	Effects.insert(std::make_pair(_KeyName, DistantSpecularEffect));
}

void D2DEffect::CreatePointSpecularEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap)
{
	// 이미 이 이펙트가 존재하는지 확인합니다.
	if (Effects.find(_KeyName) != Effects.end()) { return; }

	ID2D1Effect* pointSpecularEffect = nullptr;
	D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1PointSpecular, &pointSpecularEffect);

	// 빛의 위치 설정 (태양처럼 높은 곳에서 빛나는 효과를 만들기 위해 Z축을 높게 설정합니다)
	D2D1_VECTOR_3F lightPosition = D2D1::Vector3F(0.0f, 50.0f, 1000.0f);
	pointSpecularEffect->SetValue(D2D1_POINTSPECULAR_PROP_LIGHT_POSITION, lightPosition);

	// 표면의 스케일 설정 (높이 맵을 어떻게 해석할지 결정합니다)
	FLOAT surfaceScale = 1.0f;
	pointSpecularEffect->SetValue(D2D1_POINTSPECULAR_PROP_SURFACE_SCALE, surfaceScale);

	// 스펙큘러 상수 설정 (빛의 강도를 결정합니다)
	FLOAT specularConstant = 2.0f;
	pointSpecularEffect->SetValue(D2D1_POINTSPECULAR_PROP_SPECULAR_CONSTANT, specularConstant);

	// 스펙큘러 지수 설정 (빛의 반사 정도를 결정합니다, 높은 값일수록 빛이 날카롭게 반사됩니다)
	FLOAT specularExponent = 50.0f;
	pointSpecularEffect->SetValue(D2D1_POINTSPECULAR_PROP_SPECULAR_EXPONENT, specularExponent);

	// 빛의 색상 설정 (태양처럼 약간의 노란색을 띄게 설정합니다)
	D2D1_COLOR_F lightColor = D2D1::ColorF(1.0f, 0.9f, 0.7f);
	pointSpecularEffect->SetValue(D2D1_POINTSPECULAR_PROP_COLOR, lightColor);

	// 커널 단위 길이 설정 (효과의 세부 사항을 조절합니다)
	D2D1_VECTOR_2F kernelUnitLength = D2D1::Vector2F(1.0f, 1.0f);
	pointSpecularEffect->SetValue(D2D1_POINTSPECULAR_PROP_KERNEL_UNIT_LENGTH, kernelUnitLength);

	// 스케일 모드 설정 (고품질로 설정하여 더 부드럽게 표현)
	D2D1_POINTSPECULAR_SCALE_MODE scaleMode = D2D1_POINTSPECULAR_SCALE_MODE_LINEAR;
	pointSpecularEffect->SetValue(D2D1_POINTSPECULAR_PROP_SCALE_MODE, scaleMode);

	// 입력 비트맵 설정
	pointSpecularEffect->SetInput(0, _Bitmap);

	// 이펙트를 저장
	Effects.insert(std::make_pair(_KeyName, pointSpecularEffect));

}



