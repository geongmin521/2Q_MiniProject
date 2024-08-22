#include "pch.h"
#include "EnemyFunc.h"
#include "TowerBase.h"
#include "EnemyBase.h"
#include "IDamageNotify.h"
#include "Arrow.h"
#include "Pools.h"
#include "Effect.h"
#include "Transform.h"
void EnemyFunc::NormalAttack(GameObject* target, float Damage)
{
	IDamageNotify* nofity = dynamic_cast<IDamageNotify*>(target);
	nofity->Hit(Damage);
}

void EnemyFunc::BombAttack(EnemyBase* origin, GameObject* target, float Damage)
{
	if (origin->enemyData.name == "BombEnemy")
	{
		Effect* effect = dynamic_cast<Effect*>(Pools::GetInstance().get()->PopPool(2011));
		effect->Init(origin->GetWorldLocation(), 1.3f); //이펙트 생성
	}
	IDamageNotify* nofity = dynamic_cast<IDamageNotify*>(target);
	nofity->Hit(Damage);
	origin->curHP = 0;
}

void EnemyFunc::RangedAttack(GameObject* target, MathHelper::Vector2F pos, float Damage)
{
	if (target != nullptr)
	{
		Arrow* arrow = dynamic_cast<Arrow*>(Pools::GetInstance().get()->PopPool(601));
		arrow->Init(pos, target);
	}

}
void EnemyFunc::BossAttack(EnemyBase* origin, GameObject* target, float Damage)
{
	Effect* effect = dynamic_cast<Effect*>(Pools::GetInstance().get()->PopPool(2012));
	effect->Init({ target->GetWorldLocation().x,  target->GetWorldLocation().y + 50 }, 1.0f); //이펙트 생성
	IDamageNotify* nofity = dynamic_cast<IDamageNotify*>(target);
	nofity->Hit(Damage);
}

void EnemyFunc::spawnBat(MathHelper::Vector2F pos)
{
	for (int i = 0; i < 3; i++)
	{
		int randomPos = Utility::RandomBetween(-4, 4);
		EnemyBase* Bat = dynamic_cast<EnemyBase*>(Pools::GetInstance().get()->PopPool(102));
		Bat->transform->SetRelativeLocation({ pos.x - 50, pos.y + (-90 + i * 90) });
		Bat->curHP = Bat->enemyData.HP; //여기서 체력 초기화해주기.. 지금까지는 어떻게 되고있던거지?
		Bat->isSpawned = true;
	}
}
