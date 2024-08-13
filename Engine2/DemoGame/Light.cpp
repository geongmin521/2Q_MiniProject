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
	AddComponent(new Bitmap(L"..\\Data\\Image\\LightBackground.png"));
	AddComponent(new BoxCollider(boundBox, CollisionType::Overlap, this, CollisionLayer::Enemy));
	renderOrder = 0;
	transform->SetRelativeLocation({ 0, 0 });
	SetBoundBox(0, 0, 40, 36);

	AddComponent(new Bitmap(L"..\\Data\\Image\\afternoon.png"));
	auto bitmap = GetComponent<Bitmap>()->bitmap;

	firstBitmap = dynamic_cast<Bitmap*>(ownedComponents[1]);
	secondBitmap = dynamic_cast<Bitmap*>(ownedComponents[3]);
	D2DEffect::GetInstance()->Create2DAffineTransform(L"2DAffineTransform", bitmap, &transform->worldTransform);

	LightTransform = new Transform();
	AddComponent(LightTransform);
	D2DEffect::GetInstance()->CreateSpecularEffect(L"Specular", bitmap, LightTransform);

	D2DEffect::GetInstance()->CreateGaussianBlurEffect(L"Blur", bitmap, 10.f);
	D2DEffect::GetInstance()->CreateDistantDiffuseEffect(L"LightEffect", bitmap);
	D2DEffect::GetInstance()->CreatePointSpecularEffect(L"Point", bitmap);
	D2DEffect::GetInstance()->CreateEdgeEffect(L"EdgeEffect", bitmap);
	

	D2DEffect::GetInstance()->CreateCrossFadeEffect(L"CrossFadeEffect", firstBitmap->bitmap, secondBitmap->bitmap);

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
	ID2D1Effect* BlendEffect = D2DEffect::GetInstance()->FindEffect(L"BlendEffect");
	ID2D1Effect* CrossFadeEffect = D2DEffect::GetInstance()->FindEffect(L"CrossFadeEffect");

	ID2D1Effect* lightEffect = D2DEffect::GetInstance()->FindEffect(L"LightEffect");
	ID2D1Effect* pointEffect = D2DEffect::GetInstance()->FindEffect(L"Point");
	ID2D1Effect* Specular = D2DEffect::GetInstance()->FindEffect(L"Specular");


//	blurEffect->SetInputEffect(0, colorEffect);
//	lightEffect->SetInputEffect(0, blurEffect); 
//	EdgeEffect->SetInputEffect(0, colorEffect);
//	Affine->SetInputEffect(0, lightEffect);

//	Specular->SetInputEffect(0, colorEffect);
//	Specular->SetInputEffect(0, BlendEffect);
//	Specular->SetInputEffect(0, lightEffect);

	colorEffect->SetInputEffect(0, pointEffect); // 컬러 변경에 라이트효과을 넣었을때
	BlendEffect->SetInputEffect(0, pointEffect); // 최종 어떤 비트맵이랑 합쳐서 보여줄지
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

	// 라이트 트랜스폼 관리
	if (inputSystem->isKeyDown(VK_NUMPAD3))
	{
		LightTransform->AddRelativeLocation(10, 0);
		UpdateLightEffect();
	}

	if (inputSystem->isKeyDown(VK_NUMPAD1))
	{
		LightTransform->AddRelativeLocation(-10, 0);
		UpdateLightEffect();
	}

	if (inputSystem->isKeyDown(VK_NUMPAD5))
	{
		LightTransform->AddRelativeLocation(0, -10);
		UpdateLightEffect();
	}

	if (inputSystem->isKeyDown(VK_NUMPAD2))
	{
		LightTransform->AddRelativeLocation(0, 10);
		UpdateLightEffect();
	}

	static float elapsedTime = 0.0f;
	elapsedTime += deltaTime;

	// 1초 동안 0에서 1로 가중치가 변화하도록 설정
	float weight = elapsedTime;
	if (weight > 1.0f) weight = 1.0f;

	ID2D1Effect* crossFadeEffect = D2DEffect::GetInstance()->FindEffect(L"CrossFadeEffect");
	crossFadeEffect->SetValue(D2D1_CROSSFADE_PROP_WEIGHT, weight);

	if (weight >= 1.0f) 
	{
		// 교차 페이드 완료 시 새로운 이미지를 입력으로 설정
		ID2D1Bitmap* newBitmap = dynamic_cast<Bitmap*>(ownedComponents[3])->bitmap;
		crossFadeEffect->SetInput(0, newBitmap);
		crossFadeEffect->SetValue(D2D1_CROSSFADE_PROP_WEIGHT, 0.0f); // 가중치를 다시 초기화
		elapsedTime = 0.0f; // 시간을 초기화하여 새로운 페이드를 시작
	}
	
}

void Light::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	pRenderTarget->SetTransform(transform->worldTransform);
	if (test == true)
	{
		D2DRenderer::GetInstance()->DeviceContext->DrawImage(D2DEffect::GetInstance()->FindEffect(L"CrossFadeEffect"));
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

void Light::UpdateLightEffect()
{
	ID2D1Effect* Specular = D2DEffect::GetInstance()->FindEffect(L"Specular");
	if (Specular)
	{
		D2D1_VECTOR_3F lightPosition = D2D1::Vector3F(LightTransform->GetWorldLocation().x, LightTransform->GetWorldLocation().y, 1500.0f); // z값에 증가할수록 빛은 커짐
		D2D1_VECTOR_3F pointsAt = D2D1::Vector3F(LightTransform->GetWorldLocation().x, LightTransform->GetWorldLocation().y, 0.0f);

		Specular->SetValue(D2D1_SPOTSPECULAR_PROP_LIGHT_POSITION, lightPosition);
		Specular->SetValue(D2D1_SPOTSPECULAR_PROP_POINTS_AT, pointsAt);
	}

	ID2D1Effect* Point = D2DEffect::GetInstance()->FindEffect(L"Point");
	if (Point)
	{
		D2D1_VECTOR_3F lightPosition = D2D1::Vector3F(LightTransform->GetWorldLocation().x, LightTransform->GetWorldLocation().y, 1500.0f); // z값에 증가할수록 빛은 커짐
		D2D1_VECTOR_3F pointsAt = D2D1::Vector3F(LightTransform->GetWorldLocation().x, LightTransform->GetWorldLocation().y, 0.0f);

		Point->SetValue(D2D1_SPOTSPECULAR_PROP_LIGHT_POSITION, lightPosition);
		Point->SetValue(D2D1_SPOTSPECULAR_PROP_POINTS_AT, pointsAt);
	}
}


