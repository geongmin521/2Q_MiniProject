#include "../D2DEngine/pch.h"
#include "TowerBase.h"
#include "TowerFsm.h"
#include "../D2DEngine/FiniteStateMachine.h"


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
	//공격 사거리내에 적들어오면 TowerAttack로 전이 적이여러명인대 다 들고있어야하나 타워마다 사정거리가 다른대 다 다르게 만들어야하나 어떤타워인지 확인?
	//tower->towerData.attackRange < 적 x or y좌표   Attack으로 
}

void TowerIdle::ExitState()
{
}

void TowerAttack::EnterState()
{
	//다른 종류의 투사체를 한개에서 구별? 어떤 타워인지 확인한후 해야하나
}

void TowerAttack::Update(float DeltaTime)
{
	//거리안에 적이없으면 Idle로
	tower->Attack(DeltaTime);
}

void TowerAttack::ExitState()
{
}