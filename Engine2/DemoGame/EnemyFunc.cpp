#include "pch.h"
#include "EnemyFunc.h"
#include "TowerBase.h"
#include "EnemyBase.h"
#include "IDamageNotify.h"
#include "Arrow.h"
#include "Pools.h"
#include "Transform.h"
void EnemyFunc::NormalAttack(GameObject* target, float Damage)
{
	IDamageNotify* nofity = dynamic_cast<IDamageNotify*>(target);
	nofity->Hit(Damage);
}

void EnemyFunc::BombAttack(EnemyBase* origin, GameObject* target, float Damage)
{
	IDamageNotify* nofity = dynamic_cast<IDamageNotify*>(target);
	nofity->Hit(Damage);
	origin->curHP = 0;
}

void EnemyFunc::RangedAttack(GameObject* target, MathHelper::Vector2F pos, float Damage)
{
	Arrow* arrow = new Arrow("Vampire", 10, 3);
	arrow->Init(pos, target);
}

void EnemyFunc::BossAttack(EnemyBase* origin, GameObject* target, float Damage)
{
	IDamageNotify* nofity = dynamic_cast<IDamageNotify*>(target);
	nofity->Hit(Damage);
	nofity->Heal(Damage / 4);

	// ������ ���� FSM ����?
	spawnBat(origin->GetWorldLocation());
}

void EnemyFunc::spawnBat(MathHelper::Vector2F pos)
{
	int randomPos = Utility::RandomBetween(-2, 2);
	EnemyBase* Bat = dynamic_cast<EnemyBase*>(Pools::GetInstance().get()->PopPool(102));
	Bat->transform->SetRelativeLocation({ pos.x - 50, pos.y + (50 * randomPos) });
	Bat->curHP = Bat->enemyData.HP; //���⼭ ü�� �ʱ�ȭ���ֱ�.. ���ݱ����� ��� �ǰ��ִ�����?
	Bat->curATK = Bat->enemyData.ATK;
}
