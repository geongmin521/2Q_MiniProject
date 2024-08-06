#include "../D2DEngine/pch.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/Animation.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/Music.h"



#include "Arrow.h"

Arrow::Arrow()
{
	SetBoundBox(0, 0, 40, 36);
	AddComponent(new Animation(L"..\\Data\\Image\\ken.png", L"Arrow"));
	AddComponent(new Movement(transform));
	AddComponent(new BoxCollider(boundBox, CollisionType::Block, this, CollisionLayer::Bullet));
	
	renderOrder = 100;
}

Arrow::~Arrow()
{
}

void Arrow::Update(float deltaTime)
{
	GetComponent<Movement>()->SetVelocity({ speed,  0 });
	__super::Update(deltaTime);
	
	
}

void Arrow::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}

void Arrow::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{
	
	speed = 0;
}

void Arrow::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{

}

void Arrow::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{

}

void Arrow::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}
