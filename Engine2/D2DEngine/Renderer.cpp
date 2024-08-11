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
	if (bitmap)
	{
		ResourceManager::Instance->ReleaseD2DBitmap(strBitmapFilePath);
		bitmap = nullptr;
	}
}

void Renderer::Update(float deltaTime)
{
	float CenterX = (DstRect.right - DstRect.left) / 2; //���� �ϳ�������������������ִµ�..  //���⼭ �׸���ġ�� ���ݸ�ŭ �̵������ְ��ִ°���? 
	float CenterY = (DstRect.bottom - DstRect.top) / 2; //�׸��� ��ġ�� �̰� �Ǵ°� �³�? 
	if (mirror) 
	{
		imageTransform = D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, D2D1::Point2F(CenterX, CenterY)) *
			D2D1::Matrix3x2F::Translation(-CenterX, -CenterY); 
	}
	else
	{
		imageTransform = D2D1::Matrix3x2F::Scale(1.0f, 1.0f, D2D1::Point2F(CenterX, CenterY)) *
			D2D1::Matrix3x2F::Translation(-CenterX, -CenterY);
	}
}

void Renderer::Render(ID2D1RenderTarget* pRenderTarget) //���׸����� ���� ����� ���⼭ �����ϱ�
{
	D2D1_MATRIX_3X2_F Transform = imageTransform * owner->transform->worldTransform
		* D2DRenderer::cameraTransform; 
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
