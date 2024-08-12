#include "pch.h"
#include "EnemyFunc.h"
#include "TowerBase.h"
#include "EnemyBase.h"
#include "Arrow.h"

void EnemyFunc::NormalAttack(TowerBase* target, float Damage)
{
	target->Hit(Damage);
}

void EnemyFunc::BombAttack(EnemyBase* origin,TowerBase* target, float Damage) //타겟을 아예 찾을때부터 다이나믹 캐스트를해서 보내자
{
	target->Hit(Damage);
	//아마 이펙트를 뿌리고 본인은 죽으면되는데... 
	origin->curHP = 0;
}

void EnemyFunc::RangedAttack(TowerBase* target,MathHelper::Vector2F pos, float Damage) //총알을 새로만들어서 쏘면될거고.. 
{
	Arrow* arrow = new Arrow(0.3f, L"vampire.png");
	arrow->Init(target, pos);
}
