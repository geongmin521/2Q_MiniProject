#pragma once
#include "CommonFunc.h"

class CircleCollider;
class ArrowFunc : public CommonFunc
{ 
public:
	static void AttackEnemy(GameObject* my,GameObject* target, std::string type, float damage);
	static void WaterAttack(CircleCollider& myCol,std::string type, float damage);
	static void HiddenAttack(CircleCollider& myCol,float damage);
	static void AttackEnemys(CircleCollider& myCol, float damage); //히든애로우용 
};

