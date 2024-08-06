#include "pch.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "D2DRenderer.h"
#include "Transform.h"
Renderer::Renderer(const std::wstring strFilePath)
{
	LoadD2DBitmap(strFilePath);
}

Renderer::~Renderer()
{
	/*
	if (Bitmap)
	{
		Bitmap->Release();
		Bitmap = nullptr;
	}
	*/
	if (bitmap)
	{
		ResourceManager::Instance->ReleaseD2DBitmap(strBitmapFilePath);
		bitmap = nullptr;
	}
}

void Renderer::Update(float deltaTime)
{
	if (mirror) 
	{
		imageTransform = D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, D2D1::Point2F(0, 0)) *
			D2D1::Matrix3x2F::Translation(-CenterX, CenterY); 
	}
	else
	{
		imageTransform = D2D1::Matrix3x2F::Scale(1.0f, 1.0f, D2D1::Point2F(0, 0)) * 
			D2D1::Matrix3x2F::Translation(CenterX, CenterY);
	}
}

void Renderer::Render(ID2D1RenderTarget* pRenderTarget) //어디그릴지에 대한 계산은 여기서 통일하기
{
	//MathHelper::Vector2F 
	float CenterX = -(DstRect.right - DstRect.left) / 2 * owner->transform->GetWorldScale().x; //값을 하나씩가져오고싶을때도있는데.. 
	float CenterY = -(DstRect.bottom - DstRect.top) / 2 * owner->transform->GetWorldScale().y; //그리는 위치만 이게 되는게 맞나? 

	D2D1_MATRIX_3X2_F Transform = imageTransform * owner->transform->worldTransform 
		* D2DRenderer::cameraTransform * D2D1::Matrix3x2F::Translation(CenterX, CenterY); //얘가 이미지의크기를 들고있으니까..
	//센터도 여기로 보내버릴까? //콜라이더의 위치도 이걸따라갔으면 좋겠다.. 이거지? 
	//owner->transform->SetImageCenter({ Transform.dx, Transform.dy }); 아 여기에 월드 트랜스폼이 적용되면안되는데? 
	pRenderTarget->SetTransform(Transform);
}

void Renderer::LoadD2DBitmap(const std::wstring strFilePath)
{
	ResourceManager::Instance->CreateD2DBitmapFromFile(strFilePath, &bitmap);
	strBitmapFilePath = strFilePath;
}

MathHelper::Vector2F Renderer::GetSize()
{
	MathHelper::Vector2F scale = owner->transform->GetWorldScale();
	return { bitmap->GetSize().width * scale.x , bitmap->GetSize().height * scale.y };
}
