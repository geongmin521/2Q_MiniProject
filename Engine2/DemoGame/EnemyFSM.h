#pragma once
#include "FSMState.h"

class Animation;
class Movement;
class Vampire;
class EnemyBase;
class EnemyFSM : public FSMState //얘는 추상클래스
{
public:
	EnemyFSM(FiniteStateMachine* pOwner, std::string Name);
	~EnemyFSM();
	Animation* ani;
	Movement* move;
	EnemyBase* enemy;
	float AttackTimer = 0;
};

class EnemyIdle : public EnemyFSM
{
public:
	EnemyIdle(FiniteStateMachine* pOwner, std::string Name) : EnemyFSM(pOwner, Name) {};
private:
	virtual void EnterState() override;
	virtual void Update(float deltaTime) override;
	virtual void ExitState() override;
};

class EnemyShared : public EnemyFSM
{
public:
	EnemyShared(FiniteStateMachine* pOwner, std::string Name);
private:
	virtual void EnterState() override;
	virtual void Update(float deltaTime) override;
	virtual void ExitState() override;
};

class EnemyDead : public EnemyFSM
{
public:
	EnemyDead(FiniteStateMachine* pOwner, std::string Name) : EnemyFSM(pOwner, Name) {};
private:
	virtual void EnterState() override;
	virtual void Update(float deltaTime) override;
	virtual void ExitState() override;
};

class EnemyAttack : public EnemyFSM
{
public:
	EnemyAttack(FiniteStateMachine* pOwner, std::string Name) : EnemyFSM(pOwner, Name) {};
private:
	virtual void EnterState() override;
	virtual void Update(float deltaTime) override;
	virtual void ExitState() override;
};
