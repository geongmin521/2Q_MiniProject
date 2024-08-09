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

#include "ArrowTower.h"

Light::Light()
{
	AddComponent(new Bitmap(L"..\\Data\\Image\\Light.png"));
	AddComponent(new BoxCollider(boundBox, CollisionType::Overlap, this, CollisionLayer::Enemy));
	renderOrder = 90;
	transform->SetRelativeLocation({ 0, 0 });
	SetBoundBox(0, 0, 40, 36);


	AddComponent(new Bitmap(L"..\\Data\\Image\\afternoon.png"));

//	firstBitmap = dynamic_cast<Bitmap*>(ownedComponents[1]);
//	secondBitmap = dynamic_cast<Bitmap*>(ownedComponents[3]);
	D2DEffect::GetInstance()->Create2DAffineTransform(L"Test", GetComponent<Bitmap>()->bitmap, &transform->worldTransform);

	D2DEffect::GetInstance()->CreateSpecularEffect(L"QQQ", GetComponent<Bitmap>()->bitmap);
	D2DEffect::GetInstance()->CreateGaussianBlurEffect(L"ZZZ", GetComponent<Bitmap>()->bitmap, 10.f);
	D2DEffect::GetInstance()->Create2DLightEffect(L"SSS", GetComponent<Bitmap>()->bitmap);

	ID2D1Effect* testEffect = D2DEffect::GetInstance()->FindEffect(L"Test");

	// 이펙트 체인 구성
	ID2D1Effect* lightEffect = D2DEffect::GetInstance()->FindEffect(L"SSS");
	ID2D1Effect* blurEffect = D2DEffect::GetInstance()->FindEffect(L"ZZZ");
	ID2D1Effect* specularEffect = D2DEffect::GetInstance()->FindEffect(L"QQQ");

	// 이펙트 출력을 ID2D1Image로 가져오기
	ID2D1Image* specularOutput = nullptr;
	specularEffect->GetOutput(&specularOutput);

	ID2D1Image* blurOutput = nullptr;
	blurEffect->GetOutput(&blurOutput);

	ID2D1Image* lightOutput = nullptr;
	lightEffect->GetOutput(&lightOutput);

	// 이펙트 연결
	testEffect->SetInput(1, specularOutput);  // specularEffect의 출력을 blurEffect의 입력으로 설정
	testEffect->SetInput(2, blurOutput);     // blurEffect의 출력을 lightEffect의 입력으로 설정
	testEffect->SetInput(3, lightOutput);     // lightEffect의 출력을 testEffect의 입력으로 설정


	test = true;
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
//		D2DEffect::GetInstance()->CreateBlendEffect(L"QQQ", firstBitmap->bitmap, secondBitmap->bitmap);

		D2DRenderer::GetInstance()->DeviceContext->DrawImage(D2DEffect::GetInstance()->FindEffect(L"Test"));
	}
	else
	{
		__super::Render(pRenderTarget);
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


