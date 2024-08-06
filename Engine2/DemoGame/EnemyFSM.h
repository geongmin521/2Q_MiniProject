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
	// ��� Ÿ���� ���� enemyfsm�� ����?
	// �׷��ٸ� ���� ������ �߰� �ɶ����� �ڵ尡 �����
	Vampire* vam;	// �ϴ� �⺻��
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
public:
	VampireAttack(FiniteStateMachine* pOwner, std::string Name) : EnemyFSM(pOwner, Name) {};
private:
	virtual void EnterState() override;
	virtual void Update(float deltaTime) override;
	virtual void ExitState() override;
};

class VampireHit : public EnemyFSM
{

};