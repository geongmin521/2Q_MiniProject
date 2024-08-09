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
	// Datamanager�� �б�
	// enemyData.speed;
	enemyData.speed = 50.f;
	enemyData.attackRange = 100.f;
	enemyData.attackSpeed = 1.f;
	enemyData.HP = 500.f;
	enemyData.Type = "�����";
	curHP = enemyData.HP;
	enemyData.ATK = 1;
	// �ӽ� : ĳ������ �⺻ �̹����� ũ�� + attackrange x���� (boundbox�� �߽ɰ� �ű��?)
	SetBoundBox(0, 0, 500, 500); //�⺻ �� �̹��� ������
	AddComponent(new Animation(L"..\\Data\\Image\\zombie2.png", L"Zombie2"));
	AddComponent(new BoxCollider(boundBox, CollisionType::Overlap, this, CollisionLayer::Enemy));



	HPbar = Fac->CreateGameObject<HPBar>();
	HPbar->Init(this); //���⼭ �������� �ڱ⸦ �༭ �ڱ� Ʈ������ ã�Բ�

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

