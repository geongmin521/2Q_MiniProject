#pragma once
#include "CommonFunc.h"

class TowerFunc: public CommonFunc//타워가 가질수있는 능력들
{
public:
	static void FireBullet(GameObject* target, MathHelper::Vector2F pos, float id);
	static void Heal(GameObject* my, std::vector<GameObject*>& targets);
	static void MeleeAttack(GameObject* my, std::vector<GameObject*>& targets); //근접공격
};

