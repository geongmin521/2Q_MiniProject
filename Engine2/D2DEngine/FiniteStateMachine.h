#pragma once
#include "Component.h"

class FSMState;
class FiniteStateMachine :
    public Component
{
public:
	FiniteStateMachine() = default;
	virtual ~FiniteStateMachine();
	void SetNextState(std::string stateName); 
	void SetSharedTransition(FSMState* share);

	template<typename T>
	void CreateState(const std::string StateName)
	{
		T* pState = new T(this, StateName);
		states.insert(std::make_pair(pState->GetName(), pState));
	}


protected:
	FSMState* currState = nullptr;  // 현재 상태	
	FSMState* nextState = nullptr;	// 다음 상태
	//전이가따로 없기때문에 이걸 하나더만듬
	FSMState* sharedTransition = nullptr;	// 공유전이

	std::map<std::string, FSMState*> states;	// 생성된 FSMState들을 저장하는 컨테이너

	virtual void Update(float DeltaTime);
};

