#include "pch.h"
#include "HPBar.h"
#include "EnemyBase.h"
#include "Artifact.h"
#include "D2DRenderer.h"
#include "Animation.h"
#include "FiniteStateMachine.h"
#include "Factory.h"
#include "EnemyFSM.h"
#include "Movement.h"
#include "EnemyFunc.h"
#include "Transform.h"
#include "TowerBase.h"
#include "CircleCollider.h"
#include "Circle.h"

EnemyBase::EnemyBase(EnemyData data)
{
	this->enemyData = data;
	name = "Enemy";
	id = 1001;
	curHP = enemyData.HP;
	SetBoundBox(0, 0, 50, 50); //�⺻ �� �̹��� ������ //�̰͵� ������ ���� �ɵ�? 
	AddComponent(new Animation(L"..\\Data\\Image\\zombie2.png", L"..\\Data\\CSV\\Animation\\Zombie2.csv"));
	enemyData.attackRange = 10; //�׽�Ʈ
	AddComponent(new CircleCollider(boundBox,new Circle(transform->GetWorldLocation(), enemyData.attackRange * 50), CollisionType::Overlap, this, CollisionLayer::Enemy));
	Factory().createObj<HPBar>(curHP, enemyData.HP).setParent(transform).Get<HPBar>();
	FiniteStateMachine* fsm = new FiniteStateMachine();
	AddComponent(fsm);
	fsm->CreateState<EnemyIdle>("Idle");
	fsm->CreateState<EnemyShared>("Shared");
	fsm->CreateState<EnemyAttack>("Attack");
	fsm->CreateState<EnemyDead>("Death");
	fsm->SetNextState("Idle");
	SetAbility(data.ability);
	AddComponent(new Movement(transform));
	renderOrder = 100;
}

void EnemyBase::SetAbility(std::string ability)
{
	if (ability == "None") //�븻
	{
		attack = [this]() {EnemyFunc::NormalAttack(target[0], enemyData.ATK); }; //��� �����ϰ��ǰ��ҰŸ�.. �׳� ���� ����ִ� Ÿ���� ���κ����� hit�������� Ÿ���� �ϳ��� ����ְ��ϴ¹���̸���.. 
	}
	else if (ability == "Throw") //���Ÿ�
	{
		attack = [this]() {EnemyFunc::RangedAttack(target[0], transform->GetWorldLocation(), enemyData.ATK); };
	}
	else if (ability == "Destroy") //����
	{
		attack = [this]() {EnemyFunc::BombAttack(this, target[0], enemyData.ATK); };
	}
	else if (ability == "SpawnVat") //�����ȯ ����
	{
		attack = [this]() {EnemyFunc::BombAttack(this, target[0], enemyData.ATK); };
	}
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update(float deltaTime) //Ÿ���� ������ �������Ȯ���� ����... ��Ƽ�Ƿθ��ϸ鹮���� �����ѵ�.. ��ġ������ �߰� ���� �ľ��ϱⰡ ���������.. 
{
	__super::Update(deltaTime);
	if (isHited) //�¾������
	{
		elapsedTime += deltaTime;
		if (elapsedTime > hitedTime)
		{
			isHited = false;
			elapsedTime = 0;
		}
	}
}

void EnemyBase::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
	__super::Render(pRenderTarget);
}

void EnemyBase::Hit(float damage, float knockback)
{
	float plusAttack = Artifact::GetInstance().get()->towerPower.Attack;
	float Hpdame = curHP - damage * plusAttack;  //���� ������ �������ʿ�
	if (Hpdame <= 0)
	{
		curHP = 0;
	}
	else
	{
		curHP = Hpdame;
	}
	if(knockback !=0)
	isHited = true;
	GetComponent<Movement>()->SetVelocity({ knockback,0 });
}

void EnemyBase::Attack()
{
	attack();
}

void EnemyBase::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{
}

void EnemyBase::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

void EnemyBase::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

void EnemyBase::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}
