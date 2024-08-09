#include "pch.h"
#include "TowerBase.h"
#include "TowerFsm.h"
#include "FiniteStateMachine.h"
#include "World.h"
#include "Animation.h"
#include "Transform.h"
#include "EnemyBase.h"

TowerFSM::TowerFSM(FiniteStateMachine* pOwner, std::string Name) : FSMState(pOwner, Name)
{
	tower = (TowerBase*)owner->owner;
	ani = owner->owner->GetComponent<Animation>();
	
}
TowerFSM::~TowerFSM()
{

}

void TowerFSM::EnterState()
{
}

void TowerFSM::Update(float DeltaTime)
{
}

void TowerFSM::ExitState()
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

void TowerIdle::Update(float DeltaTime)
{

	//if (tower->target != nullptr && tower->isAttack == false)
	//{
	//	owner->SetNextState("Attack");
	//}
	//if (tower->isAttack == true)
	//{
	//	cooldown += DeltaTime;
	//	if (cooldown > tower->towerData.attackSpeed)
	//	{
	//		tower->isAttack = false;
	//		cooldown = 0;
	//	}
	//}
}

void TowerIdle::ExitState()
{
}

void TowerAttack::EnterState()
{
	ani->SetAnimation(1, false);
	ani->isLoop = false;
}


void TowerAttack::Update(float DeltaTime) //�ѹ���� ���尡�����? �̰� ��ȹ���� �����..   //����ü������ ���� �������ϳ� Ÿ������ fsm�� �����ִ°� ������
{
	//�����ѹ��Ŀ� idle�� ������ �ٽ� attack?
	if (ani->IsEnd())
	{
		tower->Attack(DeltaTime);
		//tower->isAttack = true;
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
	tower->isActive = false; //Ÿ�� �ı� �ִϸ��̼��� ������ ��Ȱ��
}

void TowerDeath::ExitState()
{
}
