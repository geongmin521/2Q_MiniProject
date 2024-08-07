#include "../D2DEngine/pch.h"
#include "TowerBase.h"
#include "TowerFsm.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/World.h"
#include "../D2DEngine/Animation.h"
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
	if(tower->towerData.HP <= 0)
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
	
	
	if (tower->target == nullptr && !tower->objs.empty())
	{

		tower->ExploreTarget(tower, tower->objs);
	}

	if (tower->target != nullptr && tower->isAttack == false)
	{
		owner->SetNextState("Attack");
	}
	
	tower->towerData.attackSpeed -= DeltaTime;
	if (tower->towerData.attackSpeed < 0)
	{
		tower->isAttack = false;
		tower->towerData.attackSpeed = 1.0f;
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
\

void TowerAttack::Update(float DeltaTime)
{
	//공격한번후엔 idle로 보내고 다시 attack?
	if (ani->IsEnd())
	{
		tower->Attack(DeltaTime);
		tower->target = nullptr;
		tower->isAttack = true;
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
	if (ani->IsEnd())
	{
		tower->isActive = false; //타워 파괴 애니메이션이 끝나면 비활성
	}
}

void TowerDeath::ExitState()
{
}
