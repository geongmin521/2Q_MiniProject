#include "../D2DEngine/pch.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/Animation.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "TowerFsm.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/Music.h"
#include "../D2DEngine/World.h" 
#include "ArrowTower.h"

ArrowTower::ArrowTower()
{
	SetBoundBox(0, 0, 102, 82);
	AddComponent(new Animation(L"..\\Data\\Image\\run.png", L"Run"));

	towerData.name = "ArrowTower";                    //csv에서 읽어와서 다넣어지게끔 
	towerData.attackRange = 300.0f;
	towerData.attackSpeed = 5.0f;
	AABB* attackRange = new AABB;
	attackRange->SetExtent(towerData.attackRange, towerData.attackRange);
	//이미지가 정해지면.. 자동으로 회전의 중심좌표를 저장하기.. 
	AddComponent(new BoxCollider(boundBox ,CollisionType::Block, this, CollisionLayer::Tower));
	AddComponent(new BoxCollider(attackRange, CollisionType::Overlap, this, CollisionLayer::Tower));
	//박스는 이전에 줄어들기 전의 위치로 회전하는데 왜그러지>? 
	FiniteStateMachine* fsm = new FiniteStateMachine();
	AddComponent(fsm);
	fsm->CreateState<TowerIdle>("Idle");
	fsm->CreateState<TowerAttack>("Attack");
	fsm->CreateState<TowerShared>("Shared");

	fsm->SetNextState("Idle");                    //적이없어서 일단 attack만 테스트 
	
	renderOrder = 100;
	transform->SetRelativeLocation({200,200});
	
}

ArrowTower::~ArrowTower()
{
}

void ArrowTower::Update(float deltaTime)
{
	
	__super::Update(deltaTime);
	if (target == nullptr && !objs.empty())
	{

		ExploreTarget(*this, objs);

	}
	//Music::soundManager->GetInstance()->PlayMusic();

}

void ArrowTower::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
	//GetComponent<BoxCollider>()->aabb->Center = { 300,300 };

}

void ArrowTower::Attack(float deltaTime)
{ 
	/*attacktime -= deltaTime;
	if (attacktime <= 0)
	{
		arrows.push_back(owner->CreateGameObject<Arrow>());
		arrows.back()->transform->relativeLocation = { GetWorldLocation().x + 100.f, GetWorldLocation().y -20.f };
	
		attacktime = 3.0f;
	}*/
	arrows.push_back(owner->CreateGameObject<Arrow>());
	arrows.back()->transform->SetRelativeLocation ({ GetWorldLocation().x + 100.f, GetWorldLocation().y - 20.f });
}


void ArrowTower::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{
}

void ArrowTower::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{
	if(otherComponent->owner->name == "enemy")
	objs.push_back(otherComponent->owner);
}

void ArrowTower::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

void ArrowTower::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{
	if (otherComponent->owner->name == "enemy")
	objs.erase(std::remove(objs.begin(),objs.end(),otherComponent->owner));
}
