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

#include "Animation.h"

Light::Light()
{
	AddComponent(new Bitmap(L"..\\Data\\Image\\Tower\\HiddenTower.png"));
	renderOrder = 0;
	transform->SetRelativeLocation({ 0, 0 });
	SetBoundBox(0, 0, 40, 36);

	firstBitmap = dynamic_cast<Bitmap*>(ownedComponents[1]);


	D2D1_MATRIX_5X4_F redEmphasis =
	{
		0.5f, 0.0f, 0.0f, 1.0f, 0.9f,
		0.0f, 0.3f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.2f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f
	};

	// 24. 8 . 14 text
//	D2DEffectManager::GetInstance()->CreateGaussianBlurEffect(L"test", secondBitmap->bitmap, 10);
	D2DEffectManager::GetInstance()->CreateMorphologyEffect(L"Morphology", firstBitmap->bitmap, TestNum);


	//24. 8 . 16 test
	// D2DEffectManager::GetInstance()->CreateBorderEffect(L"Border", firstBitmap->bitmap);
	// ����Ʈ ȿ�� �׽�Ʈ
	AddComponent(new Transform());
//	LightTransform = dynamic_cast<Transform*>(ownedComponents[2]);
	D2DEffectManager::GetInstance()->CreatePointSpecularEffect(L"Specular", firstBitmap->bitmap, 0,0);
	D2DEffectManager::GetInstance()->FindIEffect<PointSpecularEffect>(L"Specular")->LightZonter = 100;

	AddComponent(new D2DFont(L"�ٶ���")); //�ؽ�Ʈ�ڽ�

	

	GetComponent<D2DFont>()->SetSize(70.f, {0, 9});
	GetComponent<D2DFont>()->SetBoxSize(200, 200);
	GetComponent<D2DFont>()->SetWriteTextFormat(D2DFontManager::GetInstance()->FindFont(L"Map"));

	AddComponent(new Animation(L"..\\Data\\Image\\Tower\\HiddenTower.png", L"..\\Data\\CSV\\TowerAni\\HiddenTower.csv"));
	AddComponent(new Bitmap(L"..\\Data\\Image\\LightBackground.png"));

	D2DEffectManager::GetInstance()->CreateBlendEffect(L"LightText", firstBitmap->bitmap, GetComponent<Bitmap>()->bitmap);
	D2DEffectManager::GetInstance()->FindEffect(L"LightText")->SetInputEffect(0,D2DEffectManager::GetInstance()->FindEffect(L"Specular"));
}

Light::~Light()
{

}

void Light::Update(float deltaTime)
{
	__super::Update(deltaTime);

	D2DEffectManager::GetInstance()->FindIEffect<PointSpecularEffect>(L"Specular")->SetLightPos(GetComponent<Animation>()->CenterPos.x, GetComponent<Animation>()->CenterPos.y);
//	D2DEffectManager::GetInstance()->FindIEffect<PointSpecularEffect>(L"Specular")->SetLightPos(100, 100);
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

	// ����Ʈ Ʈ������ ����
	if (inputSystem->isKeyDown(VK_NUMPAD3))
	{
		LightTransform->AddRelativeLocation(10, 0); // ����Ʈ ȿ��
		
		// D2DEffectManager::GetInstance()->FindIEffect<CrossFadeEffect>(L"Cross")->isFadeIn = true; // ���̵��� ���̵� �ƿ��Ҷ�
		//D2DEffectManager::GetInstance()->FindIEffect<MorphologyEffect>(L"Morphology")->val = 8;
	}

	if (inputSystem->isKeyDown(VK_NUMPAD1))
	{
		LightTransform->AddRelativeLocation(-10, 0); // ����Ʈ ȿ��
		
		//D2DEffectManager::GetInstance()->FindIEffect<CrossFadeEffect>(L"Cross")->isFadeIn = false; // ���̵��� ���̵� �ƿ��Ҷ�
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

//  �ǽð� �� ȿ�� �������� ��
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
		D2DRenderer::GetInstance()->DeviceContext->DrawImage(D2DEffectManager::GetInstance()->FindEffect(L"LightText"), { 0 ,0 }, GetComponent<Animation>()->srcRect);
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


