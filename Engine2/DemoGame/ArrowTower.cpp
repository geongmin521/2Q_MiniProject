#include "../D2DEngine/pch.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/CircleCollider.h"
#include "../D2DEngine/Circle.h"
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/Animation.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "TowerFsm.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/Music.h"
#include "../D2DEngine/World.h" 
#include "EnemyBase.h"
#include "ArrowTower.h"

ArrowTower::ArrowTower(TowerData data) : TowerBase(data)
{
	towerData.name = "ArrowTower";                    //csv에서 읽어와서 다넣어지게끔 
	towerData.attackRange = 500.0f;
	towerData.attackSpeed = 2.0f;
	towerData.HP = 20000.0f;
	curHP = towerData.HP;

	SetBoundBox(0, 0, towerData.attackRange, towerData.attackRange);
	AddComponent(new Animation(L"..\\Data\\Image\\ken.png", L"Ken"));
	AddComponent(new BoxCollider(boundBox, CollisionType::Overlap, this, CollisionLayer::Tower));

	FiniteStateMachine* fsm = new FiniteStateMachine();
	AddComponent(fsm);
	fsm->CreateState<TowerIdle>("Idle");
	fsm->CreateState<TowerAttack>("Attack");
	fsm->CreateState<TowerShared>("Shared"); 
	fsm->CreateState<TowerDeath>("Death");
	fsm->SetNextState("Idle");                 
	
	renderOrder = 100;
	transform->SetRelativeLocation({400,300});
}

ArrowTower::~ArrowTower()
{
}

void ArrowTower::Update(float deltaTime)
{

	__super::Update(deltaTime);

	//target이 현재 없을때
	//GetComponent<BoxCollider>()->collideStateCurr.begin() it;
	//it = owner name enemy;
	//Getwroldlocation  거리비교
	//	>> 제일작은걸 타겟으로
	//	얘가 죽으면 target null 아니면 타겟;
	transform->AddRelativeRotation(1);
	FindTarget(GetComponent<BoxCollider>());
	
	
}


void ArrowTower::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);	
}

void ArrowTower::Attack(float deltaTime)
{ 
	Arrow* arrow = new Arrow;
	arrow->owner = this->owner;
	arrow->Inits(target, GetWorldLocation());
	owner->m_GameObjects.push_back(arrow);    //투사체는 타겟 hit처리를 투사체에서
}

//좀더 확실하고 통제된 환경을 만들어야한다. 

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

