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
	renderOrder = 100;
	this->enemyData = data;
	name = "Enemy";
	id = 1001;
	curHP = enemyData.HP;
	SetBoundBox(0, 0, 50, 50); 

	
	AddComponent(new Animation(L"..\\Data\\Image\\Enemy\\" + Utility::convertFromString(enemyData.name) + L".png", L"..\\Data\\CSV\\EnemyAni\\" + Utility::convertFromString(enemyData.name) + L".csv"));
	transform->SetRelativeScale({ 0.4f,0.4f });
	AddComponent(new CircleCollider(boundBox,new Circle(transform->GetWorldLocation(), enemyData.detectRange), CollisionType::Overlap, this, CollisionLayer::Enemy));
	Factory().createObj<HPBar>(curHP, enemyData.HP).setParent(transform);
	FiniteStateMachine* fsm = new FiniteStateMachine();
	AddComponent(fsm);
	fsm->CreateState<EnemyIdle>("Idle");
	fsm->CreateState<EnemyShared>("Shared");
	fsm->CreateState<EnemyAttack>("Attack");
	fsm->CreateState<EnemyDead>("Death");
	fsm->CreateState<EnemyAbility>("Ability");
	fsm->SetNextState("Idle");
	SetAbility(data.ability);
	AddComponent(new Movement(transform));
	
}

void EnemyBase::SetAbility(std::string ability)
{
	if (ability == "None") //노말
	{
		attack = [this]() {EnemyFunc::NormalAttack(target[0], curATK); };
	}
	else if (ability == "Throw") //원거리
	{
		attack = [this]() {EnemyFunc::RangedAttack(target[0], transform->GetWorldLocation(), curATK); };
	}
	else if (ability == "Destroy") //폭발
	{
		attack = [this]() {EnemyFunc::BombAttack(this, target[0], curATK); };
	}
	else if (ability == "SpawnVat") //박쥐소환 보스
	{
		attack = [this]() {EnemyFunc::BossAttack(this ,target[0], curATK); };
		Ability = [this]() {EnemyFunc::spawnBat(this->GetWorldLocation()); };
	}
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update(float deltaTime) 
{	
	__super::Update(deltaTime);
	if (isHited) //맞았을경우
	{
		elapsedTime += deltaTime;
		if (elapsedTime > hitedTime)
		{
			isHited = false;
			elapsedTime = 0;
		}
	}
	if (enemyData.name == "BossEnemy")
	{
		spawnTime += deltaTime;
		if (spawnTime > 5.f)
		{
			ability();
			spawnTime = 0;
		}
	}
}

void EnemyBase::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
	__super::Render(pRenderTarget);
}

void EnemyBase::Hit(float damage, float knockback)
{
	float Hpdame = curHP - damage;  
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

void EnemyBase::Heal(float heal)
{
	float healHP = curHP;
	healHP += heal;
	if (healHP >= enemyData.HP)
		curHP = enemyData.HP;
	else
		curHP += heal;
}

void EnemyBase::Attack()
{
	attack();
}

void EnemyBase::ability()
{
	GetComponent<FiniteStateMachine>()->SetNextState("Ability");
	Ability();
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
