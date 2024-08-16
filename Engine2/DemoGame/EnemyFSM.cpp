#include "pch.h"
#include "EnemyFSM.h"
#include "FiniteStateMachine.h"
#include "GameObject.h"
#include "Animation.h"
#include "Movement.h"
#include "Transform.h"
#include "InputSystem.h"
#include "EnemyBase.h"
#include "AABB.h"
#include "TowerBase.h"
#include "CircleCollider.h"
#include "CommonFunc.h"
#include "GameManager.h"


EnemyFSM::EnemyFSM(FiniteStateMachine* pOwner, std::string Name) : FSMState(pOwner, Name)
{
	ani = owner->owner->GetComponent<Animation>();
	move = owner->owner->GetComponent<Movement>();
	enemy = (EnemyBase*)owner->owner;
}

EnemyFSM::~EnemyFSM()
{
}

void EnemyIdle::EnterState()
{
	ani->SetAnimation(0, true);
	ani->isLoop = true;
}

void EnemyIdle::Update(float deltaTime)
{
	if (enemy->target.empty() == false)
	{
		MathHelper::Vector2F targetPos = enemy->target[0]->GetWorldLocation();
		MathHelper::Vector2F curPos = enemy->GetWorldLocation();
		float length = (targetPos - curPos).Length();
		if (enemy->target.back()->GetActive() == false)
			enemy->target.clear();
		if (length < enemy->enemyData.attackRange) //공격사거리 안쪽이다.
		{
			enemy->GetComponent<Movement>()->SetVelocity({ 0 ,0 });
			owner->SetNextState("Attack");
		}
		else
		{
			MathHelper::Vector2F moveDir = (targetPos - curPos).Normalize(); 
			if(!enemy->isHited)
			enemy->GetComponent<Movement>()->SetVelocity({ moveDir * enemy->enemyData.speed * 100 }); //테스트용 그리고 csv에서는 스피드와 탐지 범위가 너무작아서 일단이렇게 박아놓음
		}
	}
	else
	{
		CommonFunc::FindTarget(*enemy->GetComponent<CircleCollider>(),"Tower",enemy->target, enemy->enemyData.detectRange);
		if (!enemy->isHited)
		enemy->GetComponent<Movement>()->SetVelocity({ -enemy->enemyData.speed * 100, 0 }); 
	}
}

void EnemyIdle::ExitState()
{
}

EnemyShared::EnemyShared(FiniteStateMachine* pOwner, std::string Name) : EnemyFSM(pOwner, Name)
{
	pOwner->SetSharedTransition(this);
}

void EnemyShared::EnterState()
{

}

void EnemyShared::Update(float deltaTime)
{
	if (enemy->curHP <= 0)
	{
		owner->SetNextState("Death");
	}

}

void EnemyShared::ExitState()
{
}

void EnemyAttack::EnterState()
{
	enemy->GetComponent<Movement>()->SetVelocity({ 0 ,0 });
	ani->SetAnimation(1, true);
	ani->isLoop = false;
}

void EnemyAttack::Update(float deltaTime)
{
	AttackTimer += deltaTime;
	if (enemy->enemyData.attackSpeed < AttackTimer) 
	{
		AttackTimer = 0;
		owner->SetNextState("Attack"); 
	}
	if (enemy->target.empty()) 
	{
		owner->SetNextState("Idle");
		return;
	}
	else
	{
		if (ani->IsEnd()) 
		{				
			enemy->Attack();
			owner->SetNextState("Idle");
			enemy->target.clear();
		}
	}
}

void EnemyAttack::ExitState()
{

}

void EnemyDead::EnterState()
{
	if (enemy->isSpawned = false)
	{
		gameManager->LiveEenmy--;
	}
	else
	{
		
	}
	// 데스 애니메이션
}

void EnemyDead::Update(float deltaTime)
{
	enemy->SetActive(false);
}

void EnemyDead::ExitState()
{
}

void EnemyAbility::EnterState()
{
	enemy->GetComponent<Movement>()->SetVelocity({ 0 ,0 });
	ani->SetAnimation(2, true);
	ani->isLoop = false;
}

void EnemyAbility::Update(float deltaTime)
{
	if (ani->IsEnd())
	{
		owner->SetNextState("Idle");
		enemy->target.clear();
	}
	
}

void EnemyAbility::ExitState()
{

}
