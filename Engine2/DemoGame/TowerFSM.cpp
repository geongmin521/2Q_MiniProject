#include "pch.h"
#include "TowerBase.h"
#include "TowerFsm.h"
#include "FiniteStateMachine.h"
#include "World.h"
#include "Animation.h"
#include "Transform.h"
#include "Pools.h"
#include "EnemyBase.h"

TowerFSM::TowerFSM(FiniteStateMachine* pOwner, std::string Name) : FSMState(pOwner, Name)
{
	tower = (TowerBase*)owner->owner;
	ani = owner->owner->GetComponent<Animation>();
	
}
TowerFSM::~TowerFSM()
{

}

TowerShared::TowerShared(FiniteStateMachine* pOwner, std::string Name) : TowerFSM(pOwner, Name)
{
	owner->SetSharedTransition(this);
}

void TowerShared::EnterState()
{
}

void TowerShared::Update(float DeltaTime)
{
	if(tower->curHP <= 0)
	{
		owner->SetNextState("Death");
	}
}

void TowerShared::ExitState()
{
}

void TowerIdle::EnterState()
{
	ani->SetAnimation(0, false);
}

void TowerIdle::Update(float DeltaTime) //Ÿ������ ���ε� ������? Ÿ���� ��ϵ� �±׸� �԰��س��µ�.. 
{
	tower->Search();
	if (tower->target.empty() == false)
	{
		cooldown += DeltaTime;

		if (cooldown > tower->towerData.attackSpeed)
		{
			cooldown = 0; 
			owner->SetNextState("Attack");
		}	
	}
	else
	{
		cooldown = tower->towerData.attackSpeed; //ù ��Ÿ��� ���� �����Դ� �����̾��� �������..
	}
}

void TowerIdle::ExitState()
{
}

void TowerAttack::EnterState()
{
	ani->SetAnimation(1, false);
	ani->isLoop = false;
}


void TowerAttack::Update(float DeltaTime) //������ �ִϸ��̼Ǻ��� ��������.. ������ �������� �������� ���װ���.. �ִϸ��̼Ǽӵ��� �����̶� ���������� �����ϴ°� �����.. 
{
	if (ani->IsEnd())
	{
		tower->Attack(DeltaTime);
		owner->SetNextState("Idle");
	}
}

void TowerAttack::ExitState()
{
}

void TowerDeath::EnterState()
{
	//ani->SetAnimation   Ÿ�� �ı� �ִϸ��̼� ����
}

void TowerDeath::Update(float DeltaTime)
{
	//if (ani->IsEnd())
	//{
	//	tower->isActive = false; //Ÿ�� �ı� �ִϸ��̼��� ������ ��Ȱ��
	//}
	Pools::GetInstance().get()->AddPool(tower);
}

void TowerDeath::ExitState()
{
}
