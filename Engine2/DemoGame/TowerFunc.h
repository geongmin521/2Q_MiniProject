#pragma once
#include "CommonFunc.h"

class TowerFunc: public CommonFunc//Ÿ���� �������ִ� �ɷµ� //�ν��Ͻ��� �����ʿ䰡�ֳ�? 
{
public:
	static void FireBullet(GameObject* target, MathHelper::Vector2F pos);
	static void Heal(std::vector<GameObject*>& targets);
	static void MeleeAttack(std::vector<GameObject*>& targets); //��������
};

