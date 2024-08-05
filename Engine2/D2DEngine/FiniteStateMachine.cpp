#include "pch.h"
#include "FiniteStateMachine.h"
#include "FSMState.h"

FiniteStateMachine::~FiniteStateMachine()
{
	for (auto& state : states)
	{
		delete state.second;
	}
	states.clear();
}

void FiniteStateMachine::Update(float DeltaTime)
{
	if (currState != nextState) //상태만 바꿔주면 자동으로 알아서 해줌
	{
		if (currState != nullptr)
		{
			currState->ExitState();
		}
		currState = nextState;
		currState->EnterState();
	}
	else
	{
		sharedTransition->Update(DeltaTime);//공유전이 먼저 돌리기
		currState->Update(DeltaTime);
	}
}

void FiniteStateMachine::SetNextState(std::string stateName)
{
	auto it = states.find(stateName);
	if (it != states.end() && it->second != currState) //현재상태와 같지않아야함
	{
		nextState = it->second;
	}
}

void FiniteStateMachine::SetSharedTransition(FSMState* share)
{
	sharedTransition = share;
}

