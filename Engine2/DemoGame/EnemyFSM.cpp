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
	ani->SetAnimation(1, true);
	ani->isLoop = true;
	//ani->Reverse();
}

void EnemyIdle::Update(float deltaTime)
{
	if (enemy->target.empty() == false)
	{
		MathHelper::Vector2F targetPos = enemy->target[0]->GetWorldLocation();
		MathHelper::Vector2F curPos = enemy->GetWorldLocation();
		float length = (targetPos - curPos).Length();

		if (length < enemy->enemyData.attackRange) //���ݻ�Ÿ� �����̴�.
		{
			enemy->GetComponent<Movement>()->SetVelocity({ 0 ,0 });
			owner->SetNextState("Attack");
		}
		else
		{
			MathHelper::Vector2F moveDir = (targetPos - curPos).Normalize(); 
			enemy->GetComponent<Movement>()->SetVelocity({ moveDir * enemy->enemyData.speed });
		}
	}
	else
	{
		CommonFunc::FindTarget(*enemy->GetComponent<CircleCollider>(),"Tower",enemy->target, enemy->enemyData.attackRange);
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
	ani->SetAnimation(0, true);
	ani->isLoop = false;
}

void EnemyAttack::Update(float deltaTime)
{
	AttackTimer += deltaTime;
	if (enemy->enemyData.attackSpeed < AttackTimer)
	{
		AttackTimer = 0;
		owner->SetNextState("Attack"); //���� ���¿��� �ٽ� �����ϱ�.. 
	}
	if (enemy->target.empty()) //���� ������ ���̵��
	{
		owner->SetNextState("Idle");
		return;
	}
	else
	{
		if (ani->IsEnd())
		{
			enemy->Attack(); //�ִϸ��̼� ������ ���� ����
		}
	}
}

void EnemyAttack::ExitState()
{

}

void EnemyDead::EnterState()
{
	// ���� �ִϸ��̼�
}

void EnemyDead::Update(float deltaTime)
{
	enemy->SetActive(false);
}

void EnemyDead::ExitState()
{
}
