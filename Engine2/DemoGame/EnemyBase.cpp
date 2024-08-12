#include "pch.h"
#include "HPBar.h"
#include "EnemyBase.h"
#include "AABB.h"
#include "Artifact.h"
#include "D2DRenderer.h"
#include "Animation.h"
#include "BoxCollider.h"
#include "FiniteStateMachine.h"
#include "Factory.h"
#include "EnemyFSM.h"
#include "Movement.h"
#include "EnemyFunc.h"
#include "Transform.h"
#include "TowerBase.h"

EnemyBase::EnemyBase(EnemyData data)
{
	this->enemyData = data;
	name = "Enemy";
	curHP = enemyData.HP;
	SetBoundBox(0, 0, 500, 500); //기본 적 이미지 사이즈 //이것도 원으로 만들어도 될듯? 
	AddComponent(new Animation(L"..\\Data\\Image\\zombie2.png", L"..\\Data\\CSV\\Zombie2.csv"));
	AddComponent(new BoxCollider(boundBox, CollisionType::Overlap, this, CollisionLayer::Enemy));
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
		attack = [this]() {EnemyFunc::NormalAttack(target, enemyData.ATK); };
	}
	else if (ability == "Throw") //원거리
	{
		attack = [this]() {EnemyFunc::RangedAttack(target, transform->GetWorldLocation(), enemyData.ATK); };
	}
	else if (ability == "Destroy") //폭발
	{
		attack = [this]() {EnemyFunc::BombAttack(this, target, enemyData.ATK); };
	}
	else if (ability == "SpawnVat") //박쥐소환 보스
	{
		attack = [this]() {EnemyFunc::BombAttack(this, target, enemyData.ATK); };
	}
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update(float deltaTime)
{
	__super::Update(deltaTime);
	if (target != nullptr && target->isActive == false) //나중에 각 오브젝트한테 isDead를 넣어줘야할듯? 
	{
		target = nullptr;
	}
}

void EnemyBase::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}


void EnemyBase::Find(Collider* ownedCol) //이거 한번만 뜯어보면괜찮지않을까? //얘를 어디서 호출해야하나.. IDLE일때?
{
	std::vector<GameObject*> towers;
	for (auto& col : ownedCol->collideStatePrev) //사실이것도 타워랑 같은 알고리즘이라.. 이것만 좀 다시 재사용하면좋을텐데.. 
	{
		if (col->owner->name == "Tower" && col->owner->isActive == true)
		{
			towers.push_back(col->owner);			
		}
	}

	float min = INT_MAX;
	float curMin;
	MathHelper::Vector2F distance;
	GameObject* curTarget = nullptr;

	if (!towers.empty())
	{
		for (auto& tower : towers)
		{
			distance = MathHelper::Vector2F(GetWorldLocation()) - MathHelper::Vector2F(tower->GetWorldLocation());
			curMin = distance.Length();
			
			if (min > curMin)
			{
				min = curMin;
				curTarget = tower;
			}
		}
	}

	if (curTarget != nullptr)
	{
		target = dynamic_cast<TowerBase*>(curTarget);
	}
}

void EnemyBase::Hit(float damage)
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
