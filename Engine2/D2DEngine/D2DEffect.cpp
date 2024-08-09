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
	// unordered_map�� find �Լ��� ����Ͽ� Ű �˻�
	auto it = Effects.find(keyName);

	if (it != Effects.end())
	{
		return it->second;
	}
	return nullptr;
}

void D2DEffect::CreateGaussianBlurEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, const float blurVal)
{
	if (Effects.find(_KeyName) != Effects.end()) { return; } // ����ó�� �ش� Ű�� ������ ������ ������ ���� ����

	ID2D1Effect* blurEffect = nullptr;
	if (nullptr == D2DRenderer::GetInstance()->DeviceContext) { return; }

	D2DRenderer::GetInstance()->DeviceContext->CreateEffect(CLSID_D2D1GaussianBlur, &blurEffect);
	if (blurEffect == nullptr) { return; }

	blurEffect->SetInput(0, _Bitmap); //�̹��� �ε��� https://learn.microsoft.com/ko-kr/windows/win32/api/d2d1_1/nf-d2d1_1-id2d1effect-setinput
	blurEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, blurVal);
	Effects.insert(std::make_pair(_KeyName, blurEffect));
//	GaussianBlurEffect->GetOutput(&D2D1Image); // ������ ȿ���� ���� https://learn.microsoft.com/ko-kr/windows/win32/api/d2d1_1/nf-d2d1_1-id2d1effect-getoutput
}

void D2DEffect::CreateColorMatrixEffect(std::wstring _KeyName, ID2D1Bitmap* _Bitmap, D2D1_MATRIX_5X4_F _ColorMatrix)
{
	if (Effects.find(_KeyName) != Effects.end()) { return; } // ����ó�� �ش� Ű�� ������ ������ ������ ���� ����

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

	FLOAT azimuth = 0.0f;// ���� ��
	//�ð� �ݴ� ������ X���� �������� XY ����� ���� ���� �����Դϴ�. ������ ���̸� 0~360�� ���̿��� �մϴ�.
	distantDiffuseEffect->SetValue(D2D1_DISTANTDIFFUSE_PROP_AZIMUTH, azimuth);

	// ������ �� ���� (0~360��)
	FLOAT elevation = 90.0f;  // ���� ��
	//ī���� Ŭ���� Y���� �������� YZ ��鿡�� ������ ���� ������ �����մϴ�. ������ ���̸� 0~360�� ���̿��� �մϴ�.
	distantDiffuseEffect->SetValue(D2D1_DISTANTDIFFUSE_PROP_ELEVATION, elevation);

	// Ȯ�� ��� ���� (0~10,000) //0���̸� ���������� ����
	FLOAT diffuseConstant = 6.f; //6�� ����� ������ ���� ��������.
	//������ ���� �翡 ���� Ȯ�� �ݻ� �����Դϴ�. �� �Ӽ��� 0���� 10,000 ���̿��� �ϸ� ������ �����ϴ�.
	distantDiffuseEffect->SetValue(D2D1_DISTANTDIFFUSE_PROP_DIFFUSE_CONSTANT, diffuseConstant);

	// ǥ�� ������ ���� (0~10,000)
	FLOAT surfaceScale = 0.0f;
    //Z ������ ���� �μ��Դϴ�. ǥ�� ������ ������ ������ 0���� 10,000 ���̿��� �մϴ�.
	distantDiffuseEffect->SetValue(D2D1_DISTANTDIFFUSE_PROP_SURFACE_SCALE, surfaceScale);
 
	// ���� ���� ����
	D2D1_VECTOR_3F lightColor = D2D1::Vector3F(0.5f, 0.5f, 0.1f); // �ణ�� �����
    //������ ������ ���Դϴ�. �� �Ӽ��� D2D1_VECTOR_3F (R, G, B)�� ����Ǹ� LR, LG, LB�� ����ϴ� �� ���˴ϴ�.
	distantDiffuseEffect->SetValue(D2D1_DISTANTDIFFUSE_PROP_COLOR, lightColor);

//	// Ŀ�� ���� ���� ����
	D2D1_VECTOR_2F kernelUnitLength = D2D1::Vector2F(1.0f, 0.5f);
 	//X �� Y �������� ǥ�� ������ �����ϴ� �� ���Ǵ� Sobel Ŀ���� ��� ũ���Դϴ�. 
    //�� �Ӽ��� Sobel �׶��̼��� dx �� dy ���� ���ε˴ϴ�. 
    //�� �Ӽ��� D2D1_VECTOR_2F(Ŀ�� ���� ���� X, Ŀ�� ���� ���� Y)�̸�(����̽� ������ �ȼ�(DIP)/Ŀ�� ����)�� ���ǵǾ� �ֽ��ϴ�. 
    //�� ȿ���� �ּ��� ������ ����Ͽ� Ŀ�� ����� ũ��� ��ġ�ϵ��� ��Ʈ���� ũ�⸦ �����մϴ�.
	distantDiffuseEffect->SetValue(D2D1_DISTANTDIFFUSE_PROP_KERNEL_UNIT_LENGTH, kernelUnitLength);

//	// ũ�� ���� ��� ���� https://learn.microsoft.com/ko-kr/windows/win32/api/d2d1effects/ne-d2d1effects-d2d1_distantdiffuse_scale_mode
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
