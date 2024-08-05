#include "../D2DEngine/pch.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/Music.h"
#include "ArrowTower.h"

ArrowTower::ArrowTower()
{
	SetBoundBox(0, 0, 100, 100);
	AddComponent(new Bitmap(L"..\\Data\\Image\\castle.png"));

	//이미지가 정해지면.. 자동으로 회전의 중심좌표를 저장하기.. 
	transform->SetImageCenter({
		GetComponent<Bitmap>()->bitmap->GetSize().width*0.2f / 2 ,GetComponent<Bitmap>()->bitmap->GetSize().height * 0.2f / 2 });
	AddComponent(new BoxCollider(boundBox ,CollisionType::Block, this, CollisionLayer::Tower));
	//박스는 이전에 줄어들기 전의 위치로 회전하는데 왜그러지>? 

	renderOrder = 100;
	transform->relativeScale = { 0.2f,0.2f };
}

ArrowTower::~ArrowTower()
{
}

void ArrowTower::Update(float deltaTime)
{
	__super::Update(deltaTime);
	Music::soundManager->GetInstance()->PlayMusic();
	//테스트용으로 회전걸어놓고 중앙을 기준으로 회전하도록만들기
	transform->AddRelativeRotation(1);
}

void ArrowTower::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
	//GetComponent<BoxCollider>()->aabb->Center = { 300,300 };
	//D2DRenderer::GetInstance()->DrawAABB(*GetComponent<BoxCollider>()->aabb); //위치가 이상한듯? 흠 잘그리는데.. 뭐한 띄워봐야하니까 원일일수있는거 다 검사해보자
}

void ArrowTower::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{
}

void ArrowTower::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

void ArrowTower::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

void ArrowTower::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}
