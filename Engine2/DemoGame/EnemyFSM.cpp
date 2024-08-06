#include "../D2DEngine/pch.h"
#include "EnemyFSM.h"
#include "Vampire.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Animation.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/InputSystem.h"

EnemyFSM::EnemyFSM(FiniteStateMachine* pOwner, std::string Name) : FSMState(pOwner, Name)
{
	ani = owner->owner->GetComponent<Animation>();
	// 애니메이션 공격이 setanimation 0번 대기가 1번 추후에 바꿀것
	move = owner->owner->GetComponent<Movement>();
	vam = (Vampire*)owner->owner;
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
	__super::Update(deltaTime);

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
	__super::Update(deltaTime);
}

void VampireShared::ExitState()
{
}

void VampireAttack::EnterState()
{
	ani->SetAnimation(0, true);
	ani->isLoop = false;
	//ani->Reverse();
}

void VampireAttack::Update(float deltaTime)
{
	__super::Update(deltaTime);
	if (ani->IsEnd())
	{
		owner->SetNextState("Idle");
	}
}

void VampireAttack::ExitState()
{
	
}
