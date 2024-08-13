#include "pch.h"
#include "EnemyBase.h"
#include "CommonFunc.h"
#include "CircleCollider.h"
#include "Circle.h"
#include "Effect.h"
#include "Pools.h"
#include "ArrowFunc.h"


void ArrowFunc::AttackEnemy(GameObject* target,std::string type, float damage)
{
	EnemyBase* enemy = dynamic_cast<EnemyBase*>(target);	//어택헀을떄 그위치에 이펙트만들고 
	enemy->Hit(Utility::CalCul(type, enemy->enemyData.Type, damage));
}

void ArrowFunc::AttackEnemys(CircleCollider& myCol, std::string type, float damage)
{
	//성수그림에서 바꾸고 성수애니메이션? 이나 약간의 딜레이 후에 사라지게끔 해야하는대
	std::vector<GameObject*> targets;
	CommonFunc::FindTargets(myCol, "Enemy", targets, myCol.circle->radius);  
	for (auto& enemy : targets)
	{
		EnemyBase* damageEnemy = dynamic_cast<EnemyBase*>(enemy);
		if (enemy != nullptr)
			damageEnemy->Hit(Utility::CalCul(type, damageEnemy->enemyData.Type, damage)); //성수형도 매개변수로 타워에서부터 받아오게끔하고
	}
	Effect* effect = dynamic_cast<Effect*>(Pools::GetInstance().get()->PopPool(2000));
	effect->Init(L"Example.png", myCol.owner->GetWorldLocation(), 0.3f); //이펙트 생성
	myCol.SetCollisionType(CollisionType::NoCollision); //한번 공격후 노콜리전
	
	
}
