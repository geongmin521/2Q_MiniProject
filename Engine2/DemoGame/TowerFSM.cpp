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


void TowerAttack::Update(float DeltaTime) //한번쏘고 가장가까운적? 이건 기획한테 물어보기..   //투사체공격을 따로 만들어야하나 타워마다 fsm을 새로주는게 나은가
{
	//공격한번후엔 idle로 보내고 다시 attack?
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
	//ani->SetAnimation   타워 파괴 애니메이션 세팅
}

void TowerDeath::Update(float DeltaTime)
{
	//if (ani->IsEnd())
	//{
	//	tower->isActive = false; //타워 파괴 애니메이션이 끝나면 비활성
	//}
	tower->isActive = false; //타워 파괴 애니메이션이 끝나면 비활성
}

void TowerDeath::ExitState()
{
}
