#include "pch.h"
#include "D2DEffectManager.h"
#include "D2DRenderer.h"
#include "Transform.h"
#include "IEffect.h"

#include "GaussianBlurEffect.h"
#include "ColorMatrixEffect.h"
#include "BlendEffect.h"
#include "PointSpecularEffect.h"

D2DEffectManager::D2DEffectManager()
{
}

D2DEffectManager::~D2DEffectManager()
{
	for (auto& pair : Effects)
	{
		if (pair.second)
		{
			pair.second->~IEffect(); 
			pair.second = nullptr; 
		}
	}
	Effects.clear(); // 전체 맵을 정리
}

ID2D1Effect* D2DEffectManager::FindEffect(const std::wstring& keyName)
{
	auto it = Effects.find(keyName);

	if (it != Effects.end())
	{
		return it->second->DefaultEffect;
	}
	return nullptr;
}

void D2DEffectManager::Update(float deltaTime)
{
	for (auto& effectPair : Effects)
	{
		IEffect* effect = effectPair.second;
		if (effect)
		{
			effect->EffectUpdate(deltaTime);
		}
	}
}

void D2DEffectManager::Render(ID2D1RenderTarget* pRenderTarget)
{

}

void D2DEffectManager::CreateGaussianBlurEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, const float blurVal)
{
	if (Effects.find(_KeyName) != Effects.end()) { return; }
	if (nullptr == D2DRenderer::GetInstance()->DeviceContext) { return; }

	IEffect* newEffect = new GaussianBlurEffect(_Bitmap);
	dynamic_cast<GaussianBlurEffect*>(newEffect)->DefaultEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, blurVal);
	Effects.insert(std::make_pair(_KeyName, newEffect));
}

void D2DEffectManager::CreateColorMatrixEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, D2D1_MATRIX_5X4_F _ColorMatrix)
{
	if (Effects.find(_KeyName) != Effects.end()) { return; }
	if (nullptr == D2DRenderer::GetInstance()->DeviceContext) { return; }

	IEffect* newEffect = new ColorMatrixEffect(_Bitmap);
	dynamic_cast<ColorMatrixEffect*>(newEffect)->ColorMatrix = _ColorMatrix;
	Effects.insert(std::make_pair(_KeyName, newEffect));
}
// | Red Multiplier | Green Multiplier | Blue Multiplier | Alpha Multiplier | Red Offset   |
// |-------------------- | -------------------- | -------------------- | -------------------- | --------------|
// | Green Multiplier | Red Multiplier | Blue Multiplier | Alpha Multiplier | Green Offset |
// | Blue Multiplier | Green Multiplier | Red Multiplier | Alpha Multiplier | Blue Offset  |
// | Alpha Multiplier | Green Multiplier | Blue Multiplier | Red Multiplier | Alpha Offset |

void D2DEffectManager::CreateBlendEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, ID2D1Bitmap* _BitmapTwo)
{
	if (Effects.find(_KeyName) != Effects.end()) { return; }
	if (nullptr == D2DRenderer::GetInstance()->DeviceContext) { return; }

	IEffect* newEffect = new BlendEffect(_Bitmap, _BitmapTwo);
	Effects.insert(std::make_pair(_KeyName, newEffect));
}


//	void D2DEffectManager::CreateDistantDiffuseEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap)
//	{
//		if (Effects.find(_KeyName) != Effects.end()) { return; }
//		ID2D1Effect* distantDiffuseEffect = nullptr;
//		D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1DistantDiffuse, &distantDiffuseEffect);
//		distantDiffuseEffect->SetInput(0, _Bitmap);
//		FLOAT azimuth = 0.0f;// 예제 값
//		//시계 반대 방향의 X축을 기준으로 XY 평면의 광원 방향 각도입니다. 단위는 도이며 0~360도 사이여야 합니다.
//		distantDiffuseEffect->SetValue(D2D1_DISTANTDIFFUSE_PROP_AZIMUTH, azimuth);
//	
//		// 광원의 고도 설정 (0~360도)
//		FLOAT elevation = 90.0f;  // 예제 값
//		//카운터 클록의 Y축을 기준으로 YZ 평면에서 광원의 방향 각도를 지정합니다. 단위는 도이며 0~360도 사이여야 합니다.
//		distantDiffuseEffect->SetValue(D2D1_DISTANTDIFFUSE_PROP_ELEVATION, elevation);
//	
//		// 확산 상수 설정 (0~10,000) //0값이면 검은색으로 보임
//		FLOAT diffuseConstant = 6.f; //6이 연노랑 원본과 제일 유사했음.
//		//들어오는 광원 양에 대한 확산 반사 비율입니다. 이 속성은 0에서 10,000 사이여야 하며 단위가 없습니다.
//		distantDiffuseEffect->SetValue(D2D1_DISTANTDIFFUSE_PROP_DIFFUSE_CONSTANT, diffuseConstant);
//	
//		// 표면 스케일 설정 (0~10,000)
//		FLOAT surfaceScale = 0.0f;
//		//Z 방향의 배율 인수입니다. 표면 눈금은 단위가 없으며 0에서 10,000 사이여야 합니다.
//		distantDiffuseEffect->SetValue(D2D1_DISTANTDIFFUSE_PROP_SURFACE_SCALE, surfaceScale);
//	
//		// 조명 색상 설정
//		D2D1_VECTOR_3F lightColor = D2D1::Vector3F(0.5f, 0.5f, 0.1f); // 약간의 노란색
//		//들어오는 조명의 색입니다. 이 속성은 D2D1_VECTOR_3F (R, G, B)로 노출되며 LR, LG, LB를 계산하는 데 사용됩니다.
//		distantDiffuseEffect->SetValue(D2D1_DISTANTDIFFUSE_PROP_COLOR, lightColor);
//	
//		//	// 커널 유닛 길이 설정
//		D2D1_VECTOR_2F kernelUnitLength = D2D1::Vector2F(1.0f, 0.5f);
//		//X 및 Y 방향으로 표면 보통을 생성하는 데 사용되는 Sobel 커널의 요소 크기입니다. 
//		//이 속성은 Sobel 그라데이션의 dx 및 dy 값에 매핑됩니다. 
//		//이 속성은 D2D1_VECTOR_2F(커널 단위 길이 X, 커널 단위 길이 Y)이며(디바이스 독립적 픽셀(DIP)/커널 단위)에 정의되어 있습니다. 
//		//이 효과는 쌍선형 보간을 사용하여 커널 요소의 크기와 일치하도록 비트맵의 크기를 조정합니다.
//		distantDiffuseEffect->SetValue(D2D1_DISTANTDIFFUSE_PROP_KERNEL_UNIT_LENGTH, kernelUnitLength);
//	
//		//	// 크기 조정 모드 설정 https://learn.microsoft.com/ko-kr/windows/win32/api/d2d1effects/ne-d2d1effects-d2d1_distantdiffuse_scale_mode
//		D2D1_DISTANTDIFFUSE_SCALE_MODE scaleMode = D2D1_DISTANTDIFFUSE_SCALE_MODE_LINEAR;
//		distantDiffuseEffect->SetValue(D2D1_DISTANTDIFFUSE_PROP_SCALE_MODE, scaleMode);
//		Effects.insert(std::make_pair(_KeyName, distantDiffuseEffect));
//	}
//	
//	
//	void D2DEffectManager::CreateMorphologyEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, int val)
//	{
//		if (Effects.find(_KeyName) != Effects.end()) { return; }
//		ID2D1Effect* morphologyEffect;
//		D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1Morphology, &morphologyEffect);
//		morphologyEffect->SetInput(0, _Bitmap);
//	
//		morphologyEffect->SetValue(D2D1_MORPHOLOGY_PROP_MODE, D2D1_MORPHOLOGY_MODE_ERODE);
//		morphologyEffect->SetValue(D2D1_MORPHOLOGY_PROP_WIDTH, val);
//		Effects.insert(std::make_pair(_KeyName, morphologyEffect));
//	}
//	//D2D1_MATRIX_5X4_F redEmphasis =
//	//		{
//	//		0.5f, 0.0f, 0.0f, 1.0f, 0.9f,
//	//		0.0f, 0.3f, 0.0f, 0.0f, 0.0f,
//	//		0.0f, 0.0f, 0.2f, 0.0f, 0.0f,
//	//		0.0f, 0.0f, 0.0f, 0.0f, 0.0f
//	//		};
//	
//	void D2DEffectManager::CreateCrossFadeEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, ID2D1Bitmap* _BitmapTwo)
//	{
//		if (Effects.find(_KeyName) != Effects.end()) { return; }
//	
//		ID2D1Effect* CrossFadeEffect = NULL;
//		D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1CrossFade, &CrossFadeEffect);
//	
//		CrossFadeEffect->SetInput(0, _Bitmap);
//		CrossFadeEffect->SetInput(1, _BitmapTwo);
//	
//		CrossFadeEffect->SetValue(D2D1_CROSSFADE_PROP_WEIGHT, 0.5f);
//	
//		Effects.insert(std::make_pair(_KeyName, CrossFadeEffect));
//	}
//	
//	void D2DEffectManager::CreateSpecularEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, Transform* LightTransform)
//	{
//		if (Effects.find(_KeyName) != Effects.end()) { return; }
//		ID2D1Effect* SpecularEffect;
//		D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1SpotSpecular, &SpecularEffect);
//	
//		// 광원의 위치 설정 (x, y, z)
//		D2D1_VECTOR_3F lightPosition = D2D1::Vector3F(0.0f, 0.0f, 1000.0f); // 적절한 값으로 설정
//		SpecularEffect->SetValue(D2D1_SPOTSPECULAR_PROP_LIGHT_POSITION, lightPosition);
//		// 조명의 포커스 위치 설정
//		D2D1_VECTOR_3F pointsAt = D2D1::Vector3F(LightTransform->GetWorldLocation().x, LightTransform->GetWorldLocation().y, 0.0f); // 포커스 위치
//		SpecularEffect->SetValue(D2D1_SPOTSPECULAR_PROP_POINTS_AT, pointsAt);
//		// 포커스 설정 (0에서 200 사이)
//		SpecularEffect->SetValue(D2D1_SPOTSPECULAR_PROP_FOCUS, 150.0f);
//		// 제한 원뿔 각도 설정 (0~90도)
//		SpecularEffect->SetValue(D2D1_SPOTSPECULAR_PROP_LIMITING_CONE_ANGLE, 90.0f);
//		// 반사광 지수 설정 (1.0에서 128 사이)
//		SpecularEffect->SetValue(D2D1_SPOTSPECULAR_PROP_SPECULAR_EXPONENT, 40.0f);
//		// 반사 상수 설정 (0에서 10,000 사이)
//		SpecularEffect->SetValue(D2D1_SPOTSPECULAR_PROP_SPECULAR_CONSTANT, 1.0f); // 빛 약하게 만들수 있음
//		// 표면 스케일 설정
//		SpecularEffect->SetValue(D2D1_SPOTSPECULAR_PROP_SURFACE_SCALE, 2.0f);
//	
//		D2D1_VECTOR_2F kernelUnitLength = D2D1::Vector2F(1.0f, 1.0f); // x와 y 방향의 커널 유닛 길이 설정
//		SpecularEffect->SetValue(D2D1_POINTSPECULAR_PROP_KERNEL_UNIT_LENGTH, kernelUnitLength);
//		// 조명의 색상 설정
//		D2D1_VECTOR_3F lightColor = D2D1::Vector3F(1.0f, 1.0f, 1.0f); // 백색 조명
//		SpecularEffect->SetValue(D2D1_SPOTSPECULAR_PROP_COLOR, lightColor);
//	
//		SpecularEffect->SetInput(0, _Bitmap);
//		Effects.insert(std::make_pair(_KeyName, SpecularEffect));
//	}
//	
//	void D2DEffectManager::CreateDistanSpecularEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap)
//	{
//		if (Effects.find(_KeyName) != Effects.end()) { return; }
//		ID2D1Effect* DistantSpecularEffect;
//		D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1DistantSpecular, &DistantSpecularEffect);
//		DistantSpecularEffect->SetValue(D2D1_DISTANTSPECULAR_PROP_AZIMUTH, 180.0f);  // 방위각
//		DistantSpecularEffect->SetValue(D2D1_DISTANTSPECULAR_PROP_ELEVATION, 90.0f); // 고도 (태양이 머리 위에서 비추는 효과)
//		DistantSpecularEffect->SetValue(D2D1_DISTANTSPECULAR_PROP_SPECULAR_EXPONENT, 50.0f); // 반사 지수 (더 강한 반사)
//		DistantSpecularEffect->SetValue(D2D1_DISTANTSPECULAR_PROP_SPECULAR_CONSTANT, 1.0f); // 반사 상수 (광원의 밝기 증가)
//		DistantSpecularEffect->SetValue(D2D1_DISTANTSPECULAR_PROP_SURFACE_SCALE, 5.0f);    // 표면 스케일 (높이 증가)
//		DistantSpecularEffect->SetValue(D2D1_DISTANTSPECULAR_PROP_COLOR, D2D1::Vector3F(1.0f, 0.95f, 0.8f)); // 조명 색상 (태양빛 색상)
//		DistantSpecularEffect->SetValue(D2D1_DISTANTSPECULAR_PROP_KERNEL_UNIT_LENGTH, D2D1::Vector2F(1.0f, 1.0f)); // 커널 단위 길이
//		DistantSpecularEffect->SetValue(D2D1_DISTANTSPECULAR_PROP_SCALE_MODE, D2D1_DISTANTSPECULAR_SCALE_MODE_HIGH_QUALITY_CUBIC); // 스케일 모드 (고품질)
//	
//		DistantSpecularEffect->SetInput(0, _Bitmap);
//		Effects.insert(std::make_pair(_KeyName, DistantSpecularEffect));
//	}
//	
void D2DEffectManager::CreatePointSpecularEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, Transform* _Transform)
{
	if (Effects.find(_KeyName) != Effects.end()) { return; }
	if (nullptr == D2DRenderer::GetInstance()->DeviceContext) { return; }

	IEffect* newEffect = new PointSpecularEffect(_Bitmap, _Transform);
	Effects.insert(std::make_pair(_KeyName, newEffect));

	// 마스크 비트맵을 이펙트에 적용   이거 왜 했는지 기억 안나서 일단 주석
//	ID2D1Effect* maskEffect = nullptr;
//	D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1BitmapSource, &maskEffect);
//	maskEffect->SetInput(0, _Bitmap);
//	pointSpecularEffect->SetInputEffect(1, maskEffect);

}

//	void D2DEffectManager::Create2DAffineTransform(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, D2D1_MATRIX_3X2_F* matrix)
//	{
//		if (Effects.find(_KeyName) != Effects.end()) { return; }
//		ID2D1Effect* affineTransform;
//		D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D12DAffineTransform, &affineTransform);
//		affineTransform->SetInput(0, _Bitmap);
//		affineTransform->SetValue(D2D1_2DAFFINETRANSFORM_PROP_TRANSFORM_MATRIX, matrix);
//		Effects.insert(std::make_pair(_KeyName, affineTransform));
//	}
//	
//	// https://learn.microsoft.com/ko-kr/windows/win32/api/d2d1effects_2/ne-d2d1effects_2-d2d1_edgedetection_prop
//	void D2DEffectManager::CreateEdgeEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap)
//	{
//		if (Effects.find(_KeyName) != Effects.end()) { return; }
//		ID2D1Effect* EdgeEffect;
//		D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1EdgeDetection, &EdgeEffect);
//		EdgeEffect->SetInput(0, _Bitmap);
//		EdgeEffect->SetValue(D2D1_EDGEDETECTION_PROP_STRENGTH, 0.8);
//		EdgeEffect->SetValue(D2D1_EDGEDETECTION_PROP_OVERLAY_EDGES, false);
//	
//		Effects.insert(std::make_pair(_KeyName, EdgeEffect));
//	}

