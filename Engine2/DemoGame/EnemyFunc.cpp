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
	Arrow* arrow = new Arrow("Vampire", 10, 3,5);
	arrow->Init(pos, target);
}

void EnemyFunc::BossAttack(EnemyBase* origin, GameObject* target, float Damage)
{
	IDamageNotify* nofity = dynamic_cast<IDamageNotify*>(target);
	Damage = 4;
	nofity->Hit(Damage);
	origin->Heal(Damage / 4);
}

void EnemyFunc::spawnBat(MathHelper::Vector2F pos)
{
	int randomPos = Utility::RandomBetween(-2, 2);
	EnemyBase* Bat = dynamic_cast<EnemyBase*>(Pools::GetInstance().get()->PopPool(102));
	Bat->transform->SetRelativeLocation({ pos.x - 50, pos.y + (50 * randomPos) });
	Bat->curHP = Bat->enemyData.HP; //여기서 체력 초기화해주기.. 지금까지는 어떻게 되고있던거지?
	Bat->isSpawned = true;
}
