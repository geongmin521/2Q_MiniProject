#include "../D2DEngine/pch.h"
#include "VampireRanged.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/Animation.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/BoxCollider.h"
#include "EnemyFSM.h"
#include "TowerBase.h"

VampireRanged::VampireRanged(EnemyData data) : EnemyBase(data)
{
	enemyData.speed = 300.f;
	enemyData.attackRange = 10.f;
	enemyData.attackSpeed = 1.f;
	enemyData.HP = 10.f;
	enemyData.ATK = 50.f;
	curHP = enemyData.HP;

	SetBoundBox(0, 0, 150, 180); //기본 적 이미지 사이즈
	AddComponent(new Animation(L"..\\Data\\Image\\zombie3.png", L"Zombie2"));
	AddComponent(new BoxCollider(boundBox, CollisionType::Overlap, this, CollisionLayer::Enemy));


	FiniteStateMachine* fsm = new FiniteStateMachine();
	AddComponent(fsm);
	fsm->CreateState<VampireIdle>("Idle");
	fsm->CreateState<VampireShared>("Shared");
	fsm->CreateState<VampireAttack>("Attack");
	fsm->SetNextState("Idle");

	AddComponent(new Movement(transform));

	transform->SetRelativeLocation({ 2000, 100 });

	renderOrder = 100;
}

VampireRanged::~VampireRanged()
{
}

void VampireRanged::Update(float deltaTime)
{
}

void VampireRanged::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
}

void VampireRanged::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{
}

void VampireRanged::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

void VampireRanged::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

void VampireRanged::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

void VampireRanged::Attack(float deltaTime)
{
}
