#pragma once
#include "CommonFunc.h"

class TowerFunc: public CommonFunc//Ÿ���� �������ִ� �ɷµ�
{
public:
	static void FireBullet(GameObject* target, MathHelper::Vector2F pos, float id);
	static void Heal(GameObject* my, std::vector<GameObject*>& targets);
	static void MeleeAttack(GameObject* my, std::vector<GameObject*>& targets); //��������
};

