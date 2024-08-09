#include "pch.h"
#include "BoxCollider.h"
#include "Bitmap.h"
#include "Animation.h"
#include "Transform.h"
#include "D2DRenderer.h"
#include "FiniteStateMachine.h"
#include "TowerFsm.h"
#include "AABB.h"
#include "Factory.h"
#include "Music.h"
#include "HealingTower.h"

HealingTower::HealingTower(TowerData data) : TowerBase(data)
{
	towerData.name = "HealingTower";                    //csv에서 읽어와서 다넣어지게끔 
	towerData.attackRange = 5000.0f;
	towerData.attackSpeed = 5.0f;
	towerData.HP = 20000.0f;
	curHP = towerData.HP;
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
	__super::Update(deltaTime);


	FindTarget(GetComponent<BoxCollider>(), true, true);
}

void HealingTower::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}

void HealingTower::Attack(float deltaTime)
{
	std::vector<TowerBase*> Towers;  //이름
	for (auto& tower : targets)
	{
		Towers.push_back(dynamic_cast<TowerBase*>(tower));
	}

	for (auto& tower : Towers)
	{
		tower->Heal(1000);
	}
}

void HealingTower::OnBlock(Collider* ownedComponent, Collider* otherComponent)
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
