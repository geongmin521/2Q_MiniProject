#include "../D2DEngine/pch.h"
#include "Vampire.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/Animation.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/AABB.h"
#include "EnemyFSM.h"

Vampire::Vampire()
{
	// Datamanager로 읽기
	// enemyData.speed;
	SetBoundBox(0, 0, 80, 180);
	AddComponent(new Animation(L"..\\Data\\Image\\zombie2.png", L"Zombie2"));
	AddComponent(new BoxCollider(boundBox, CollisionType::Block, this, CollisionLayer::Enemy));
	AddComponent(new Movement(transform));

	FiniteStateMachine* fsm = new FiniteStateMachine();
	AddComponent(fsm);
	fsm->CreateState<VampireIdle>("Idle");
	fsm->CreateState<VampireShared>("Shared");
	fsm->CreateState<VampireAttack>("Attack");
	fsm->SetNextState("Idle");

	renderOrder = 100;
	enemyData.ATK = 10;
	transform->SetRelativeScale ({ 3, 3 });
	enemyData.speed = 400.0f;
	transform->SetRelativeLocation( { 2000, 100 });

	searchBox = new AABB;
	enemyData.attackRange = 30.f;
	searchBox->SetExtent(enemyData.attackRange + 100.f, enemyData.attackRange + 50.f);
	searchBound = CreateComponent<BoxCollider>();
	searchBound->aabb = searchBox;
	searchBound->SetCollisionLayer(CollisionLayer::Enemy);
	searchBound->SetCollisionType(CollisionType::Overlap);
	searchBound->SetNotify(this);
	searchBound->PushCollider();
	searchBound->name = "EnemyAtk";

	//attackBound = new AABB
	//AddComponent(new BoxCollider(attackBox, CollisionType::Overlap, this, CollisionLayer::Enemy));
} 

Vampire::~Vampire()
{
}

void Vampire::Update(float deltaTime)
{
	GetComponent<Movement>()->SetVelocity({-enemyData.speed , 0 });
	__super::Update(deltaTime);
	//attackBox->SetCenter(boundBox->Center.x - 100, boundBox->Center.y);
}

void Vampire::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}

void Vampire::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{
	//enemyData.speed = 0;

	if (otherComponent->GetCollisionLayer() == CollisionLayer::Tower)
	{
		//GetComponent<FiniteStateMachine>()->SetNextState("Attack");
	}
}

void Vampire::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{

	if (otherComponent->name== "attackbox" && ownedComponent->name == "EnemyAtk")
	{
		enemyData.speed = 0;
		
		objs.push_back(otherComponent->owner);
		GetComponent<FiniteStateMachine>()->SetNextState("Attack");
		// 데미지 관련 코드 추가할 예정
	}
}

void Vampire::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

void Vampire::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}
