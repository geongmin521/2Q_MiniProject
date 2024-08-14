#include "pch.h"
#include "EnemyFunc.h"
#include "TowerBase.h"
#include "EnemyBase.h"
#include "IDamageNotify.h"
#include "Arrow.h"

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

void EnemyFunc::RangedAttack(GameObject* target,MathHelper::Vector2F pos, float Damage)
{
	Arrow* arrow = new Arrow("Vampire",10,3); 
	arrow->Init(pos, target);
}
