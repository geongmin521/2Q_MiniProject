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
	AddComponent(new Animation(L"..\\Data\\Image\\Zombie.png", L"Zombie"));
	AddComponent(new RigidBody());
	AddComponent(new BoxCollider(boundBox, CollisionType::Block, this, CollisionLayer::Enemy));
	AddComponent(new Movement(transform));
	FiniteStateMachine* fsm = new FiniteStateMachine();
	AddComponent(fsm);

	fsm->CreateState<VampireIdle>("Idle");
	fsm->CreateState<VampireShared>("Shared");
	fsm->SetNextState("Idle");

	renderOrder = 100;
	transform->relativeScale = { 3, 3 };
	transform->relativeLocation = { 0, 100 };
} 

Vampire::~Vampire()
{
}

void Vampire::Update(float deltaTime)
{
	GetComponent<Movement>()->SetVelocity({ 50.f , 0 });
	__super::Update(deltaTime);
}

void Vampire::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
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
