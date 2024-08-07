#include "../D2DEngine/pch.h"
#include "Vampire.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/Animation.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/AABB.h"
#include "EnemyFSM.h"
#include "TowerBase.h"

Vampire::Vampire()
{
	// Datamanager로 읽기
	// enemyData.speed;
	enemyData.speed = 300.f;
	enemyData.attackRange = 10.f;
	enemyData.attackSpeed = 1.f;
	enemyData.HP = 50.f;
	curHP = enemyData.HP;
	
	// 임시 : 캐릭터의 기본 이미지의 크기 + attackrange x값만 (boundbox의 중심값 옮기기?)
	SetBoundBox(0, 0, 150, 180); //기본 적 이미지 사이즈
	AddComponent(new Animation(L"..\\Data\\Image\\zombie2.png", L"Zombie2"));
	AddComponent(new BoxCollider(boundBox, CollisionType::Overlap, this, CollisionLayer::Enemy));


	FiniteStateMachine* fsm = new FiniteStateMachine();
	AddComponent(fsm);
	fsm->CreateState<VampireIdle>("Idle");
	fsm->CreateState<VampireShared>("Shared");
	fsm->CreateState<VampireAttack>("Attack");
	fsm->SetNextState("Idle");

	AddComponent(new Movement(transform));

	transform->SetRelativeLocation( { 2000, 100 });

	renderOrder = 100;
} 

Vampire::~Vampire()
{
}

void Vampire::Update(float deltaTime)
{
	
	__super::Update(deltaTime);
	

	//attackBox->SetCenter(boundBox->Center.x - 100, boundBox->Center.y);
	
	Find(GetComponent<BoxCollider>());
	
}

void Vampire::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}

void Vampire::Attack(float deltaTime)
{
	TowerBase* tower = dynamic_cast<TowerBase*>(target);
	//std::cout << tower->curHP;
	if (target != nullptr)
	{
		//tower->Hit(50);
	}
}

void Vampire::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{
	//enemyData.speed = 0;

	//if (otherComponent->GetCollisionLayer() == CollisionLayer::Tower)
	//{
	//	//GetComponent<FiniteStateMachine>()->SetNextState("Attack");
	//}
}

void Vampire::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{

	//if (otherComponent->name== "attackbox" && ownedComponent->name == "EnemyAtk")
	//{
	//	enemyData.speed = 0;
	//	
	//	objs.push_back(otherComponent->owner);
	//	GetComponent<FiniteStateMachine>()->SetNextState("Attack");
	//	// 데미지 관련 코드 추가할 예정
	//}
}

void Vampire::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

void Vampire::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

