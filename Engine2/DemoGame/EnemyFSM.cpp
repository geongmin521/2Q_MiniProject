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
	// 애니메이션 공격이 setanimation 0번 대기가 1번 추후에 바꿀것
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
void VampireIdle::EnterState()
{
	ani->SetAnimation(1, true);
	ani->isLoop = true;
	//ani->Reverse();
}

void VampireIdle::Update(float deltaTime)
{
	// 몸통크기 165.f 
	
	if (enemy->target != nullptr)
	{
		MathHelper::Vector2F targetPos = enemy->target->GetWorldLocation();
		MathHelper::Vector2F curPos = enemy->GetWorldLocation();
		// 추적범위 일정하게 설정할것 
		// 눈대중으로 대충 맞춤 스피드가 달라지면 판정값도 달라져야만 일정 범위를 유지할수있음

		
		if (std::abs(targetPos.x + enemy->enemyData.attackRange - curPos.x) <= 90.f)
		{
			enemy->GetComponent<Movement>()->SetVelocity({ 0 ,0 });
			if (enemy->isAttack == false)
			{
				owner->SetNextState("Attack");
			}
		}
		else
		{
			enemy->GetComponent<Movement>()->SetVelocity({ -enemy->enemyData.speed, targetPos.y - curPos.y });
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
			// 고칠 것
		}
	}
}

void VampireIdle::ExitState()
{
}

VampireShared::VampireShared(FiniteStateMachine* pOwner, std::string Name) : EnemyFSM(pOwner, Name)
{
	pOwner->SetSharedTransition(this);
}

void VampireShared::EnterState()
{

}

void VampireShared::Update(float deltaTime)
{
	if (enemy->curHP <= 0)
	{
		enemy->isActive = false;
	}

}

void VampireShared::ExitState()
{
}

void VampireAttack::EnterState()
{
	enemy->GetComponent<Movement>()->SetVelocity({ 0 ,0 });
	ani->SetAnimation(0, true);
	ani->isLoop = false;

	//ani->Reverse();
}

void VampireAttack::Update(float deltaTime)
{
	if (ani->IsEnd())
	{
		enemy->isAttack = true;
		//enemy->target = nullptr;
		enemy->Attack(deltaTime);
	
		owner->SetNextState("Idle");
	}
}

void VampireAttack::ExitState()
{

}
