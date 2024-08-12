#pragma once
class GameObject;
class EnemyBase;
class EnemyFunc
{
public:
	static void NormalAttack(GameObject* target, float Damage);
	static void BombAttack(EnemyBase* origin, GameObject* target, float Damage);
	static void RangedAttack(GameObject* target, MathHelper::Vector2F pos, float Damage);
};

