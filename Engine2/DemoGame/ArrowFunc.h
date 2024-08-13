#pragma once
#include "CommonFunc.h"

class CircleCollider;
class ArrowFunc : public CommonFunc
{ 
public:
	static void  AttackEnemy(GameObject* target, std::string type, float damage);
	static void  AttackEnemys(CircleCollider& mycol,std::string type, float damage);
};

