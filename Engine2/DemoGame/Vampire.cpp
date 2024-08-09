#include "pch.h"
#include "Vampire.h"
#include "Transform.h"
#include "FiniteStateMachine.h"
#include "Animation.h"
#include "Movement.h"
#include "D2DRenderer.h"
#include "AABB.h"
#include "EnemyFSM.h"
#include "Factory.h"
#include "TowerBase.h"

Vampire::Vampire(EnemyData data) : EnemyBase(data)
{
	// Datamanager로 읽기
	// enemyData.speed;
	enemyData.speed = 50.f;
	enemyData.attackRange = 100.f;
	enemyData.attackSpeed = 1.f;
	enemyData.HP = 500.f;
	enemyData.Type = "방어형";
	curHP = enemyData.HP;
	enemyData.ATK = 1;
	// 임시 : 캐릭터의 기본 이미지의 크기 + attackrange x값만 (boundbox의 중심값 옮기기?)
	SetBoundBox(0, 0, 500, 500); //기본 적 이미지 사이즈
	AddComponent(new Animation(L"..\\Data\\Image\\zombie2.png", L"Zombie2"));
	AddComponent(new BoxCollider(boundBox, CollisionType::Overlap, this, CollisionLayer::Enemy));



	HPbar = Fac->CreateGameObject<HPBar>();
	HPbar->Init(this); //여기서 주인으로 자기를 줘서 자기 트랜스폼 찾게끔

	FiniteStateMachine* fsm = new FiniteStateMachine();
	AddComponent(fsm);
	fsm->CreateState<EnemyIdle>("Idle");
	fsm->CreateState<EnemyShared>("Shared");
	fsm->CreateState<EnemyAttack>("Attack");
	fsm->CreateState<EnemyDead>("Death");
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
		tower->Hit(enemyData.ATK);
	}
}

void Vampire::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{

}

void Vampire::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{


}

void Vampire::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

void Vampire::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

