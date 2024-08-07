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
void VampireIdle::EnterState()
{
	ani->SetAnimation(1, true);
	ani->isLoop = true;
	//ani->Reverse();
}

void VampireIdle::Update(float deltaTime)
{
	// ����ũ�� 165.f 

	if(enemy->target != nullptr && enemy->isAttack == false && 
		std::abs(enemy->target->GetWorldLocation().x   - enemy->GetWorldLocation().x) <= dynamic_cast<TowerBase*>(enemy->target)->towerData.attackRange / 4)
		// csv�� ���� ũ�� ������
	{
		owner->SetNextState("Attack");
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

}

void VampireShared::ExitState()
{
}

void VampireAttack::EnterState()
{
	enemy->enemyData.speed = 0;
	ani->SetAnimation(0, true);
	ani->isLoop = false;
	//ani->Reverse();
}

void VampireAttack::Update(float deltaTime)
{
	if (ani->IsEnd())
	{
		enemy->isAttack = true;
		enemy->target = nullptr;
		owner->SetNextState("Idle");
	}
}

void VampireAttack::ExitState()
{
	
}
