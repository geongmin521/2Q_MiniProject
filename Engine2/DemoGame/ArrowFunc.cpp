#include "pch.h"
#include "EnemyBase.h"
#include "CommonFunc.h"
#include "CircleCollider.h"
#include "Circle.h"
#include "Effect.h"
#include "Pools.h"
#include "Arrow.h"
#include "ArrowFunc.h"


void ArrowFunc::AttackEnemy(GameObject* my,GameObject* target,std::string type, float damage)
{
	// 추후에 아티팩트 기반으로 데미지 고정값 증가
	EnemyBase* enemy = dynamic_cast<EnemyBase*>(target);	//어택헀을떄 그위치에 이펙트만들고 
	MathHelper::Vector2F dir = (enemy->GetWorldLocation() - my->GetWorldLocation()).Normalize();
	enemy->Hit(Utility::CalCul(type, enemy->enemyData.Type, damage), 100); //일단 100
	Pools::GetInstance().get()->AddPool(my);
}

void ArrowFunc::WaterAttack(CircleCollider& myCol, std::string type, float damage)
{
	
	//성수그림에서 바꾸고 성수애니메이션? 이나 약간의 딜레이 후에 사라지게끔 해야하는대
	std::vector<GameObject*> targets;
	CommonFunc::FindTargets(myCol, "Enemy", targets, myCol.circle->radius);  
	for (auto& enemy : targets)
	{
		EnemyBase* damageEnemy = dynamic_cast<EnemyBase*>(enemy);
		if (enemy != nullptr)
		{
			MathHelper::Vector2F dir = (enemy->GetWorldLocation() - myCol.circle->Center).Normalize();
			damageEnemy->Hit(Utility::CalCul(type, damageEnemy->enemyData.Type, damage), 100);
		}
	}
	
	Effect* effect = dynamic_cast<Effect*>(Pools::GetInstance().get()->PopPool(2000));
	effect->Init(L"Light.png", myCol.owner->GetWorldLocation(), 0.3f); //이펙트 생성
	myCol.SetCollisionType(CollisionType::NoCollision); //한번 공격후 노콜리전
	Pools::GetInstance().get()->AddPool(myCol.owner);
	
}

void ArrowFunc::HiddenAttack(CircleCollider& myCol,float damage)
{
	
	Arrow* arrow = dynamic_cast<Arrow*>(Pools::GetInstance().get()->PopPool(513)); //513만따로 히든애로우용 으로?
	arrow->Init(myCol.owner->GetWorldLocation());
	Pools::GetInstance().get()->AddPool(myCol.owner);
}

void ArrowFunc::AttackEnemys(CircleCollider& myCol, float damage)
{
	std::vector<GameObject*> targets;
	CommonFunc::FindTargets(myCol, "Enemy", targets, myCol.circle->radius);
	for (auto& enemy : targets)
	{
		EnemyBase* damageEnemy = dynamic_cast<EnemyBase*>(enemy);
		if (enemy != nullptr)
		{
			damageEnemy->Hit(damage);
		}
	}
	

}


