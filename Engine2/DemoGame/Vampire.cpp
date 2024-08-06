#include "../D2DEngine/pch.h"
#include "Vampire.h"
#include "../D2DEngine/Animation.h"
#include "../D2DEngine/RigidBody.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/BoxCollider.h"
#include "EnemyFSM.h"

Vampire::Vampire()
{
	// Datamanager·Î ÀÐ±â
	//enemyData.speed;
	SetBoundBox(0, 0, 80, 180);
	AddComponent(new Animation(L"..\\Data\\Image\\zombie2.png", L"Zombie2"));
	AddComponent(new RigidBody());
	AddComponent(new BoxCollider(boundBox, CollisionType::Block,this, CollisionLayer::Enemy));
	AddComponent(new Movement(transform));
	FiniteStateMachine* fsm = new FiniteStateMachine();
	AddComponent(fsm);
	fsm->CreateState<VampireIdle>("Idle");
	fsm->CreateState<VampireShared>("Shared");
	fsm->SetNextState("Idle");
	renderOrder = 100;
	enemyData.ATK = 10;
	transform->SetRelativeScale ({ 3, 3 });
	enemyData.speed = -200.0f;
	transform->SetRelativeLocation( { 2000, 100 });
	name = "Enemy";
	
} 

Vampire::~Vampire()
{
}

void Vampire::Update(float deltaTime)
{
	GetComponent<Movement>()->SetVelocity({enemyData.speed , 0 });
	__super::Update(deltaTime);
}

void Vampire::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}

void Vampire::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{
	//enemyData.speed = 0;
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
