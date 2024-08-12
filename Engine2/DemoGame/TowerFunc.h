#pragma once
#include "CommonFunc.h"

class TowerFunc: public CommonFunc//타워가 가질수있는 능력들 //인스턴스를 가질필요가있나? 
{
public:
	static void FireBullet(GameObject* target, MathHelper::Vector2F pos);
	static void Heal(std::vector<GameObject*>& targets);
	static void MeleeAttack(std::vector<GameObject*>& targets); //근접공격
};

