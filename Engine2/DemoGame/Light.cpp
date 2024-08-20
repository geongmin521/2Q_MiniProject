#include "pch.h"
#include "D2DRenderer.h"
#include "D2DEffectManager.h"
#include "Movement.h"
#include "Transform.h"
#include "Bitmap.h"
#include "InputSystem.h"
#include "World.h"
#include "Animation.h"
#include "BoxCollider.h"
#include "Light.h"

#include "D2DFont.h"
#include "D2DFontManager.h"

#include "GaussianBlurEffect.h"
#include "CrossFadeEffect.h"
#include "MorphologyEffect.h"
#include "PointSpecularEffect.h"
#include "BorderEffect.h"

Light::Light()
{
	AddComponent(new Bitmap(L"..\\Data\\Image\\afternoon.png"));
	renderOrder = 0;
	transform->SetRelativeLocation({ 0, 0 });
	SetBoundBox(0, 0, 40, 36);

	AddComponent(new Bitmap(L"..\\Data\\Image\\night.png"));
	auto bitmap = GetComponent<Bitmap>()->bitmap;

	firstBitmap = dynamic_cast<Bitmap*>(ownedComponents[1]);
	secondBitmap = dynamic_cast<Bitmap*>(ownedComponents[2]);

	D2D1_MATRIX_5X4_F redEmphasis =
	{
		0.5f, 0.0f, 0.0f, 1.0f, 0.9f,
		0.0f, 0.3f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.2f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f
	};

//	blurEffect->SetInputEffect(0, colorEffect);
//	lightEffect->SetInputEffect(0, blurEffect); 
//	EdgeEffect->SetInputEffect(0, colorEffect);
//	Affine->SetInputEffect(0, lightEffect);

//	Specular->SetInputEffect(0, colorEffect);
//	Specular->SetInputEffect(0, BlendEffect);
//	Specular->SetInputEffect(0, lightEffect);

//	colorEffect->SetInputEffect(0, pointEffect); // 컬러 변경에 라이트효과을 넣었을때
//	BlendEffect->SetInputEffect(0, pointEffect); // 최종 어떤 비트맵이랑 합쳐서 보여줄지
//	ID2D1Effect* Cross = D2DEffectManager::GetInstance()->FindEffect(L"CrossFadeEffect");
//	blurEffect->SetInputEffect(0, Cross);

	// 24. 8 . 14 text
	D2DEffectManager::GetInstance()->CreateGaussianBlurEffect(L"test", secondBitmap->bitmap, 10);
	D2DEffectManager::GetInstance()->CreateCrossFadeEffect(L"Cross", firstBitmap->bitmap, secondBitmap->bitmap);
	D2DEffectManager::GetInstance()->CreateMorphologyEffect(L"Morphology", firstBitmap->bitmap, TestNum);

	//24. 8 . 16 test
//	D2DEffectManager::GetInstance()->CreateBorderEffect(L"Border", firstBitmap->bitmap);
	// 라이트 효과 테스트
	AddComponent(new Transform());
	LightTransform = dynamic_cast<Transform*>(ownedComponents[3]);
	D2DEffectManager::GetInstance()->CreatePointSpecularEffect(L"Specular", firstBitmap->bitmap, LightTransform);
	D2DEffectManager::GetInstance()->FindIEffect<PointSpecularEffect>(L"Specular")->LightZonter = 100;

	AddComponent(new D2DFont(L"다람쥐"));
	D2DFontManager::GetInstance()->LoadFont(L"..\\Data\\Font\\DNFBitBitv2.ttf", L"Test");
	D2DFontManager::GetInstance()->LoadFont(L"..\\Data\\Font\\Maplestory Bold.ttf", L"Map");
	
	GetComponent<D2DFont>()->SetSize(70.f, {0, 9});
	GetComponent<D2DFont>()->SetBoxSize(200, 200);
	GetComponent<D2DFont>()->SetWriteTextFormat(D2DFontManager::GetInstance()->FindFont(L"Map"));
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
		LightTransform->AddRelativeLocation(10, 0); // 라이트 효과
		
		// D2DEffectManager::GetInstance()->FindIEffect<CrossFadeEffect>(L"Cross")->isFadeIn = true; // 페이드인 페이드 아웃할때
		//D2DEffectManager::GetInstance()->FindIEffect<MorphologyEffect>(L"Morphology")->val = 8;
	}

	if (inputSystem->isKeyDown(VK_NUMPAD1))
	{
		LightTransform->AddRelativeLocation(-10, 0); // 라이트 효과
		
		//D2DEffectManager::GetInstance()->FindIEffect<CrossFadeEffect>(L"Cross")->isFadeIn = false; // 페이드인 페이드 아웃할때
		//D2DEffectManager::GetInstance()->FindIEffect<MorphologyEffect>(L"Morphology")->val = 2;
	}

	if (inputSystem->isKeyDown(VK_NUMPAD5))
	{
		LightTransform->AddRelativeLocation(0, -10);
	}

	if (inputSystem->isKeyDown(VK_NUMPAD2))
	{
		LightTransform->AddRelativeLocation(0, 10);
	}

//  실시간 블러 효과 넣을려고 함
//	static float timetest = 0;
//	timetest += deltaTime * 10;
//	auto blurEffect = D2DEffectManager::GetInstance()->FindIEffect<GaussianBlurEffect>(L"test");
//	blurEffect->blurVal = timetest;  
	
}

void Light::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
	pRenderTarget->SetTransform(transform->worldTransform);
	if (test == true)
	{
//		D2DRenderer::GetInstance()->DeviceContext->DrawImage(D2DEffectManager::GetInstance()->FindEffect(L"Border"));
	}
	else
	{
		D2DRenderer::GetInstance()->DrawGradientCircle(D2D1::Point2F(300, 300), 100.0f, D2D1::ColorF(D2D1::ColorF::White));
		__super::Render(pRenderTarget);
	}
}

void Light::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{
}

void Light::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{

}

void Light::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{

}

void Light::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{

}


