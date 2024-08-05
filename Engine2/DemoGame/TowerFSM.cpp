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
	//���� ��Ÿ����� �������� TowerAttack�� ���� ���̿������δ� �� ����־���ϳ� Ÿ������ �����Ÿ��� �ٸ��� �� �ٸ��� �������ϳ� �Ÿ������ Ȯ��?
	//tower->towerData.attackRange < �� x or y��ǥ   Attack���� 
}

void TowerIdle::ExitState()
{
}

void TowerAttack::EnterState()
{
	//�ٸ� ������ ����ü�� �Ѱ����� ����? � Ÿ������ Ȯ������ �ؾ��ϳ�
}

void TowerAttack::Update(float DeltaTime)
{
	//�Ÿ��ȿ� ���̾����� Idle��
	tower->Attack(DeltaTime);
}

void TowerAttack::ExitState()
{
}