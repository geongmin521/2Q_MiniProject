#include "../D2DEngine/pch.h"
#include "VampireBomb.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/Animation.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/BoxCollider.h"
#include "EnemyFSM.h"

VampireBomb::VampireBomb(EnemyData data) :EnemyBase(data)
{
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
	transform->SetRelativeScale({ 3, 3 });
	enemyData.speed = 400.0f;
	transform->SetRelativeLocation({ 2000, 100 });

	attackBox = new AABB;
	enemyData.attackRange = 10.f;
	attackBox->SetExtent(100.f + enemyData.attackRange, 60.f + enemyData.attackRange);
	AddComponent(new BoxCollider(attackBox, CollisionType::Overlap, this, CollisionLayer::Enemy));
}

VampireBomb::~VampireBomb()
{

}

void VampireBomb::Update(float deltaTime)
{
	GetComponent<Movement>()->SetVelocity({ -enemyData.speed , 0 });
	__super::Update(deltaTime);
}

void VampireBomb::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}

void VampireBomb::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{
	enemyData.speed = 0;

	if (otherComponent->GetCollisionLayer() == CollisionLayer::Tower)
	{
		//GetComponent<FiniteStateMachine>()->SetNextState("Attack");
	}
}

void VampireBomb::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{
	if (otherComponent->GetCollisionLayer() == CollisionLayer::Tower)
	{
		GetComponent<FiniteStateMachine>()->SetNextState("Attack");
	}
}

void VampireBomb::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{

}

void VampireBomb::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{

}
