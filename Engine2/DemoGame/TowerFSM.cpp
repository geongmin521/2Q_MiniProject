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

void TowerIdle::Update(float DeltaTime) //타겟으로 본인도 들어오나? 타겟은 등록된 태그만 먹게해놨는데.. 
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
		cooldown = tower->towerData.attackSpeed; //첫 사거리에 들어온 적에게는 딜레이없이 쏘기위함..
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


void TowerAttack::Update(float DeltaTime) //공속이 애니메이션보다 빨라지면.. 공속이 느려지는 잠재적인 버그가능.. 애니메이션속도가 공속이랑 같아지도록 세팅하는거 만들기.. 
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
	//ani->SetAnimation   타워 파괴 애니메이션 세팅
}

void TowerDeath::Update(float DeltaTime)
{
	//if (ani->IsEnd())
	//{
	//	tower->isActive = false; //타워 파괴 애니메이션이 끝나면 비활성
	//}
	Pools::GetInstance().get()->AddPool(tower);
}

void TowerDeath::ExitState()
{
}
