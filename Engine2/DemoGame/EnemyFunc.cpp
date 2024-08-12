#include "pch.h"
#include "EnemyFunc.h"
#include "TowerBase.h"
#include "EnemyBase.h"
#include "IDamageNotify.h"
#include "Arrow.h"

void EnemyFunc::NormalAttack(GameObject* target, float Damage) //이것을 어떻게 들고있으면좋을려나.. 
{
	IDamageNotify* nofity = dynamic_cast<IDamageNotify*>(target);
	nofity->Hit(Damage);
}

void EnemyFunc::BombAttack(EnemyBase* origin, GameObject* target, float Damage) //타겟을 아예 찾을때부터 다이나믹 캐스트를해서 보내자
{
	IDamageNotify* nofity = dynamic_cast<IDamageNotify*>(target);
	nofity->Hit(Damage);
	//아마 이펙트를 뿌리고 본인은 죽으면되는데... 
	origin->curHP = 0;
}

void EnemyFunc::RangedAttack(GameObject* target,MathHelper::Vector2F pos, float Damage) //총알을 새로만들어서 쏘면될거고.. 
{
	Arrow* arrow = new Arrow(0.3f, L"vampire.png");
	arrow->Init(target, pos);
}
