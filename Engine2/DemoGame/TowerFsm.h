#pragma once
#include "../D2DEngine/FSMState.h"

class TowerFSM : public FSMState
{
public:
	TowerFSM(FiniteStateMachine* pOwner, std::string Name);
	~TowerFSM();
	virtual void EnterState()override;
	virtual void Update(float DeltaTime) override;
	virtual void ExitState() override;
};

class TowerShared : public TowerFSM //공유전이입니다. 현재 상태를 업데이트하기전에 호출되어 공유전이의 특정조건을 만족하면 상태를 전이합니다. 
{
public:
	TowerShared(FiniteStateMachine* pOwner, std::string Name);
private:
	virtual void EnterState() override;
	virtual void Update(float DeltaTime) override;
	virtual void ExitState() override;
};

class TowerIdle : public TowerFSM //모든 타워가 같은 상태머신을 공유하지않을까?  여기서 다른 매커니즘으로 작동하는 타워가존재할수있을까?
{
public:
	TowerIdle(FiniteStateMachine* pOwner, std::string Name) : TowerFSM(pOwner, Name) {};
private:
	virtual void EnterState() override;
	virtual void Update(float DeltaTime) override;
	virtual void ExitState() override;
};

