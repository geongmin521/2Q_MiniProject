#pragma once
#include "CommonFunc.h"
class TowerBase;
class TowerFunc: public CommonFunc//Ÿ���� �������ִ� �ɷµ�
{
public:
	static void FireBullet(TowerBase* my,GameObject* target, MathHelper::Vector2F pos, float id);
	static void Heal(std::vector<GameObject*>& targets, float heal);
	static void MeleeAttack(GameObject* my,std::vector<GameObject*>& targets); //��������
};

