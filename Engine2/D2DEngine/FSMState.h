#pragma once

class FiniteStateMachine;
class FSMState
{
public:
	FSMState(FiniteStateMachine* pOwner, std::string Name)
		:owner(pOwner)
		, name(Name)
	{

	}
	virtual ~FSMState()
	{

	}
	std::string name;
	FiniteStateMachine* owner;

public:
	void SetOwner(FiniteStateMachine* pOwner) { owner = pOwner; }

	const std::string& GetName() { return name; }

	virtual void EnterState() = 0;	// 상태 진입전 실행할 내용
	virtual void Update(float DeltaTime) = 0; // 상태 일때 계속 실행할 내용, 전이 조건 검사 (Check Transition Condition) 도 같이 한다.
	virtual void ExitState() = 0;	// 상태 탈출때 실행할 내용
};
