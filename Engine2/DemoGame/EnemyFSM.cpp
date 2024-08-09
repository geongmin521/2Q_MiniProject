#include "../D2DEngine/pch.h"
#include "EnemyFSM.h"
#include "Vampire.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Animation.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/InputSystem.h"
#include "EnemyBase.h"
#include "../D2DEngine/AABB.h"
#include "TowerBase.h"

EnemyFSM::EnemyFSM(FiniteStateMachine* pOwner, std::string Name) : FSMState(pOwner, Name)
{
	ani = owner->owner->GetComponent<Animation>();
	// �ִϸ��̼� ������ setanimation 0�� ��Ⱑ 1�� ���Ŀ� �ٲܰ�
	move = owner->owner->GetComponent<Movement>();
	//vam = (Vampire*)owner->owner;
	enemy = (EnemyBase*)owner->owner;
}

EnemyFSM::~EnemyFSM()
{
}

void EnemyFSM::EnterState()
{
}

void EnemyFSM::Update(float deltaTime)
{

}

void EnemyFSM::ExitState()
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
	// ����ũ�� 165.f 
	
	if (enemy->target != nullptr)
	{
		MathHelper::Vector2F targetPos = enemy->target->GetWorldLocation();
		MathHelper::Vector2F curPos = enemy->GetWorldLocation();
		// �������� �����ϰ� �����Ұ� 
		// ���������� ���� ���� ���ǵ尡 �޶����� �������� �޶����߸� ���� ������ �����Ҽ�����

		
		if (std::abs(targetPos.x  - curPos.x) <= enemy->enemyData.attackRange / 2)
		{
			enemy->GetComponent<Movement>()->SetVelocity({ 0 ,0 });
			if (enemy->isAttack == false)
			{
				owner->SetNextState("Attack");
			}
		}
		else
		{
			MathHelper::Vector2F moveDir = (targetPos - curPos).Normalize(); 
			enemy->GetComponent<Movement>()->SetVelocity({ moveDir * enemy->enemyData.speed });
		}
	}
	else
	{
		enemy->GetComponent<Movement>()->SetVelocity({ -enemy->enemyData.speed , 0 });
	}

	if (enemy->isAttack == true)
	{
		enemy->enemyData.attackSpeed -= deltaTime;
		if (enemy->enemyData.attackSpeed < 0)
		{
			enemy->isAttack = false;
			enemy->enemyData.attackSpeed = 1.0f;
			// ��ĥ ��
		}
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
	if (ani->IsEnd())
	{
		enemy->Attack(deltaTime);
		enemy->isAttack = true;
		owner->SetNextState("Idle");
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
	enemy->isActive = false;
}

void EnemyDead::ExitState()
{
}
