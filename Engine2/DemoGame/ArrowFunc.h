#pragma once
#include "CommonFunc.h"

class Arrow;
class CircleCollider;
class ArrowFunc : public CommonFunc
{ 
public:
	static void AttackEnemy(Arrow* my,GameObject* target, std::string type, float damage, float knockBack);
	static void AttackTower(GameObject* my, GameObject* target, std::string type, float damage, float knockBack);
	static void WaterAttack(Arrow* my, CircleCollider& myCol,std::string type, float damage, float knockBack);
	static void HiddenAttack(CircleCollider& myCol,float damage);
	static void AttackEnemys(CircleCollider& myCol, float damage, float knockBack); //히든애로우용 
};

