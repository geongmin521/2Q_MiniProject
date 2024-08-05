#pragma once
#include "../D2DEngine/FSMState.h"

class Animation;
class Movement;
class Vampire;
class EnemyFSM : public FSMState
{
public:
	EnemyFSM(FiniteStateMachine* pOwner, std::string Name);
	~EnemyFSM();

	virtual void EnterState() override;
	virtual void Update(float deltaTime) override;
	virtual void ExitState() override;

	Animation* ani;
	Movement* move;
	// 모든 타입의 적을 enemyfsm에 정리?
	// 그렇다면 적의 종류가 추가 될때마다 코드가 길어짐
	Vampire* vam;	// 일단 기본형
};

class VampireIdle : public EnemyFSM
{
public:
	VampireIdle(FiniteStateMachine* pOwner, std::string Name) : EnemyFSM(pOwner, Name) {};
private:
	virtual void EnterState() override;
	virtual void Update(float deltaTime) override;
	virtual void ExitState() override;
};

class VampireShared : public EnemyFSM
{
public:
	VampireShared(FiniteStateMachine* pOwner, std::string Name);
private:
	virtual void EnterState() override;
	virtual void Update(float deltaTime) override;
	virtual void ExitState() override;
};

class VampireDead : public EnemyFSM
{

};

class VampireAttack : public EnemyFSM
{

};

class VampireHit : public EnemyFSM
{

};