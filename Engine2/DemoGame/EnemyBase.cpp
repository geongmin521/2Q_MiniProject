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
	SetBoundBox(0, 0, 50, 50); //기본 적 이미지 사이즈 //이것도 원으로 만들어도 될듯? 
	AddComponent(new Animation(L"..\\Data\\Image\\zombie2.png", L"..\\Data\\CSV\\Animation\\Zombie2.csv"));
	enemyData.attackRange = 10; //테스트
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
	if (ability == "None") //노말
	{
		attack = [this]() {EnemyFunc::NormalAttack(target[0], enemyData.ATK); }; //사실 정말일관되게할거면.. 그냥 현재 들고있는 타겟을 전부보내서 hit을때리고 타겟을 하나만 들고있게하는방식이맞지.. 
	}
	else if (ability == "Throw") //원거리
	{
		attack = [this]() {EnemyFunc::RangedAttack(target[0], transform->GetWorldLocation(), enemyData.ATK); };
	}
	else if (ability == "Destroy") //폭발
	{
		attack = [this]() {EnemyFunc::BombAttack(this, target[0], enemyData.ATK); };
	}
	else if (ability == "SpawnVat") //박쥐소환 보스
	{
		attack = [this]() {EnemyFunc::BombAttack(this, target[0], enemyData.ATK); };
	}
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update(float deltaTime) //타겟을 여러개 들고있을확률도 있음... 노티피로만하면문제가 없긴한데.. 위치값등의 추가 값을 파악하기가 힘들수있음.. 
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
}

void EnemyBase::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
	__super::Render(pRenderTarget);
}

void EnemyBase::Hit(float damage, float knockback)
{
	float plusAttack = Artifact::GetInstance().get()->towerPower.Attack;
	float Hpdame = curHP - damage * plusAttack;  //예시 변수명 수정등필요
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
