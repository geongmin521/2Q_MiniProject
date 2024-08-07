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
#include "HealingTower.h"

HealingTower::HealingTower()
{
	towerData.name = "HealingTower";                    //csv에서 읽어와서 다넣어지게끔 
	towerData.attackRange = 300.0f;
	towerData.attackSpeed = 1.0f;
	curHP = 200.0f;

	SetBoundBox(0, 0, 500, 500); // 근접타워 높이는 자기 몸체크기만큼
	AddComponent(new Animation(L"..\\Data\\Image\\ken.png", L"MeleeTower")); //일단 켄 같이쓰고 근접공격 애니메이션만 다르게
	AddComponent(new BoxCollider(boundBox, CollisionType::Overlap, this, CollisionLayer::Tower));

	FiniteStateMachine* fsm = new FiniteStateMachine();
	AddComponent(fsm);
	fsm->CreateState<TowerIdle>("Idle");
	fsm->CreateState<TowerAttack>("Attack");
	fsm->CreateState<TowerShared>("Shared");
	fsm->CreateState<TowerDeath>("Death");
	fsm->SetNextState("Idle");

	renderOrder = 100;
	transform->SetRelativeLocation({ 200,100 });
}

HealingTower::~HealingTower()
{
}

void HealingTower::Update(float deltaTime)
{
}

void HealingTower::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
}

void HealingTower::Attack(float deltaTime)
{
}

void HealingTower::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

void HealingTower::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

void HealingTower::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}
