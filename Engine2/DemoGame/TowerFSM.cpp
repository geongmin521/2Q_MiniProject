#include "../D2DEngine/pch.h"
#include "TowerBase.h"
#include "TowerFsm.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/World.h"
#include "EnemyBase.h"

TowerFSM::TowerFSM(FiniteStateMachine* pOwner, std::string Name) : FSMState(pOwner, Name)
{
	tower = (TowerBase*)owner->owner;
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
}

void TowerShared::ExitState()
{
}

void TowerIdle::EnterState()
{

}

void TowerIdle::Update(float DeltaTime)
{
	

	
	if (tower->target != nullptr)
	{
		owner->SetNextState("Attack");
	}
	

}

void TowerIdle::ExitState()
{
}

void TowerAttack::EnterState()
{

}

void TowerAttack::Update(float DeltaTime)
{
	//공격한번후엔 idle로 보내고 다시 attack?
	tower->Attack(DeltaTime);
	tower->target = nullptr;
	//owner->SetNextState("Idle");
}

void TowerAttack::ExitState()
{
}