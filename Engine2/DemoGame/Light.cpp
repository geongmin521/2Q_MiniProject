#include "pch.h"
#include "D2DRenderer.h"
#include "D2DEffect.h"
#include "Movement.h"
#include "Transform.h"
#include "Bitmap.h"
#include "InputSystem.h"
#include "World.h"
#include "Animation.h"
#include "BoxCollider.h"
#include "Light.h"

Light::Light()
{
	AddComponent(new Bitmap(L"..\\Data\\Image\\Light.png"));
	AddComponent(new BoxCollider(boundBox, CollisionType::Overlap, this, CollisionLayer::Enemy));
	renderOrder = 90;
	transform->SetRelativeLocation({ 0, 0 });
	SetBoundBox(0, 0, 40, 36);

	AddComponent(new Bitmap(L"..\\Data\\Image\\afternoon.png"));
	auto bitmap = GetComponent<Bitmap>()->bitmap;

	firstBitmap = dynamic_cast<Bitmap*>(ownedComponents[1]);
	secondBitmap = dynamic_cast<Bitmap*>(ownedComponents[3]);
	D2DEffect::GetInstance()->Create2DAffineTransform(L"2DAffineTransform", bitmap, &transform->worldTransform);
	D2DEffect::GetInstance()->CreateSpecularEffect(L"Specular", bitmap);

	D2DEffect::GetInstance()->CreateGaussianBlurEffect(L"Blur", bitmap, 10.f);
	D2DEffect::GetInstance()->Create2DLightEffect(L"LightEffect", bitmap);
	D2DEffect::GetInstance()->CreatePointSpecularEffect(L"Point", bitmap);
	D2DEffect::GetInstance()->CreateEdgeEffect(L"EdgeEffect", bitmap);
	

	D2D1_MATRIX_5X4_F redEmphasis =
	{
		0.5f, 0.0f, 0.0f, 1.0f, 0.9f,
		0.0f, 0.3f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.2f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f
	};
	D2DEffect::GetInstance()->CreateColorMatrixEffect(L"Color", bitmap, redEmphasis);
	D2DEffect::GetInstance()->CreateBlendEffect(L"BlendEffect", firstBitmap->bitmap, secondBitmap->bitmap);


	ID2D1Effect* EdgeEffect = D2DEffect::GetInstance()->FindEffect(L"EdgeEffect");
	ID2D1Effect* Affine = D2DEffect::GetInstance()->FindEffect(L"2DAffineTransform");
	ID2D1Effect* colorEffect = D2DEffect::GetInstance()->FindEffect(L"Color");
	ID2D1Effect* blurEffect = D2DEffect::GetInstance()->FindEffect(L"Blur");
	ID2D1Effect* lightEffect = D2DEffect::GetInstance()->FindEffect(L"LightEffect");
	ID2D1Effect* Specular = D2DEffect::GetInstance()->FindEffect(L"Specular");
	ID2D1Effect* BlendEffect = D2DEffect::GetInstance()->FindEffect(L"BlendEffect");
	

	blurEffect->SetInputEffect(0, colorEffect);
	lightEffect->SetInputEffect(0, blurEffect); 
	EdgeEffect->SetInputEffect(0, colorEffect);
	Affine->SetInputEffect(0, lightEffect);
	BlendEffect->SetInputEffect(0, Specular);
//	Specular->SetInputEffect(0, D2DEffect::GetInstance()->FindEffect(L"BlendEffect"));
}

Light::~Light()
{

}

void Light::Update(float deltaTime)
{
	__super::Update(deltaTime);

	if (inputSystem->isKeyDown(VK_RIGHT))
	{
		transform->AddRelativeLocation(10, 0);
	}

	if (inputSystem->isKeyDown(VK_LEFT))
	{
		transform->AddRelativeLocation(-10, 0);
	}

	if (inputSystem->isKeyDown(VK_UP))
	{
		transform->AddRelativeLocation(0, -10);
	}

	if (inputSystem->isKeyDown(VK_DOWN))
	{
		transform->AddRelativeLocation(0, 10);
	}
}

void Light::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	pRenderTarget->SetTransform(transform->worldTransform);
	if (test == true)
	{
		D2DRenderer::GetInstance()->DeviceContext->DrawImage(D2DEffect::GetInstance()->FindEffect(L"BlendEffect"));
	}
	else
	{
		__super::Render(pRenderTarget);
		D2DRenderer::GetInstance()->DrawGradientCircle(D2D1::Point2F(300, 300), 100.0f, D2D1::ColorF(D2D1::ColorF::White));
	}

}

void Light::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{
}

void Light::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{

//		D2DEffect::GetInstance()->CreateBlendEffect(L"test", GetComponent<Bitmap>()->bitmap,
//			otherComponent->owner->GetComponent<Animation>()->bitmap);

//	D2D1_MATRIX_5X4_F redEmphasis =
//	{
//	0.5f, 0.0f, 0.0f, 1.0f, 0.9f,
//	0.0f, 0.3f, 0.0f, 0.0f, 0.0f,
//	0.0f, 0.0f, 0.2f, 0.0f, 0.0f,
//	0.0f, 0.0f, 0.0f, 0.0f, 0.0f
//	};
//
//	D2DEffect::GetInstance()->CreateColorMatrixEffect(L"test", GetComponent<Bitmap>()->bitmap, redEmphasis);
		
//	D2DEffect::GetInstance()->CreateGaussianBlurEffect(L"test", GetComponent<Bitmap>()->bitmap, 10.f);
//	D2DEffect::GetInstance()->Create2DLightEffect(L"test", GetComponent<Bitmap>()->bitmap);
//	D2DEffect::GetInstance()->CreateMorphologyEffect(L"test", GetComponent<Bitmap>()->bitmap);
//	test = true;

}

void Light::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{

}

void Light::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{

}


