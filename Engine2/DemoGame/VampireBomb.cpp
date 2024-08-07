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
#include "TowerBase.h"

VampireBomb::VampireBomb()
{
	enemyData.speed = 300.f;
	enemyData.attackRange = 10.f;
	enemyData.attackSpeed = 1.f;
	enemyData.HP = 10.f;
	enemyData.ATK = 100.f;
	curHP = enemyData.HP;

	// �ӽ� : ĳ������ �⺻ �̹����� ũ�� + attackrange x���� (boundbox�� �߽ɰ� �ű��?)
	SetBoundBox(0, 0, 150, 180); //�⺻ �� �̹��� ������
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

VampireBomb::~VampireBomb()
{

}

void VampireBomb::Update(float deltaTime)
{
	__super::Update(deltaTime);
	Find(GetComponent<BoxCollider>());
}

void VampireBomb::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
	
}

void VampireBomb::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{
	
}

void VampireBomb::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{

}

void VampireBomb::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{

}

void VampireBomb::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{

}

void VampireBomb::Attack(float deltaTime)
{
	TowerBase* tower = dynamic_cast<TowerBase*>(target);
	//std::cout << tower->curHP;
	if (target != nullptr)
	{
		tower->Hit(enemyData.ATK);
		curHP -= enemyData.HP;
	}
}
