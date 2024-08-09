#pragma once
#include "FSMState.h"

class Animation;
class Movement;
class Vampire;
class EnemyBase;
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
	// ��� Ÿ���� ���� enemyfsm�� ����?
	// �׷��ٸ� ���� ������ �߰� �ɶ����� �ڵ尡 �����
	Vampire* vam;	// �ϴ� �⺻��
	EnemyBase* enemy;
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
