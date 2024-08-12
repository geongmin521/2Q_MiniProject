#pragma once
class TowerBase;
class EnemyBase;
class EnemyFunc
{
public:
	static void NormalAttack(TowerBase* target, float Damage);
	static void BombAttack(EnemyBase* origin,TowerBase* target, float Damage);
	static void RangedAttack(TowerBase* target, MathHelper::Vector2F pos, float Damage);
};

