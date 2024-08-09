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
		D2DRenderer::GetInstance()->DeviceContext->DrawImage(D2DEffect::GetInstance()->FindEffect(L"test"));
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


