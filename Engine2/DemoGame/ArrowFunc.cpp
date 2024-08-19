#include "pch.h"
#include "EnemyBase.h"
#include "CommonFunc.h"
#include "CircleCollider.h"
#include "Circle.h"
#include "Effect.h"
#include "Pools.h"
#include "Arrow.h"
#include "ArrowFunc.h"
#include "Artifact.h"

void ArrowFunc::AttackEnemy(GameObject* my,GameObject* target,std::string type, float damage, float knockBack)
{
	// 추후에 아티팩트 기반으로 데미지 고정값 증가
	EnemyBase* enemy = dynamic_cast<EnemyBase*>(target);	
	MathHelper::Vector2F dir = (enemy->GetWorldLocation() - my->GetWorldLocation()).Normalize();
	enemy->Hit(Utility::CalCul(type, enemy->enemyData.Type, damage + (artifact->BowPower.atkLevel * 2)), knockBack); //일단 100 넉백수치 받아오기필요
	Effect* effect = dynamic_cast<Effect*>(Pools::GetInstance().get()->PopPool(2001));
	effect->Init(my->GetWorldLocation(), 1.0f); //이펙트 생성
	Pools::GetInstance().get()->AddPool(my);
}

void ArrowFunc::WaterAttack(CircleCollider& myCol, std::string type, float damage, float knockBack)
{
	std::vector<GameObject*> targets;
	CommonFunc::FindTargets(myCol, "Enemy", targets, myCol.circle->radius);  
	for (auto& enemy : targets)
	{
		EnemyBase* damageEnemy = dynamic_cast<EnemyBase*>(enemy);
		if (enemy != nullptr)
		{
			MathHelper::Vector2F dir = (enemy->GetWorldLocation() - myCol.circle->Center).Normalize();
			damageEnemy->Hit(Utility::CalCul(type, damageEnemy->enemyData.Type, damage + (artifact->WaterPower.atkLevel * 2)), knockBack);
		}
	}
	

	Effect* effect = dynamic_cast<Effect*>(Pools::GetInstance().get()->PopPool(2000));
	effect->Init(myCol.owner->GetWorldLocation(), 0.25f); //이펙트 생성
	myCol.SetCollisionType(CollisionType::NoCollision); 
	Pools::GetInstance().get()->AddPool(myCol.owner);
	
}

void ArrowFunc::HiddenAttack(CircleCollider& myCol,float damage)
{
	
	Arrow* arrow = dynamic_cast<Arrow*>(Pools::GetInstance().get()->PopPool(513)); //513만따로 히든애로우용 으로?
	arrow->Init(myCol.owner->GetWorldLocation());
	Pools::GetInstance().get()->AddPool(myCol.owner);
}

void ArrowFunc::AttackEnemys(CircleCollider& myCol, float damage, float knockBack)
{
	std::vector<GameObject*> targets;
	CommonFunc::FindTargets(myCol, "Enemy", targets, myCol.circle->radius);
	for (auto& enemy : targets)
	{
		EnemyBase* damageEnemy = dynamic_cast<EnemyBase*>(enemy);
		if (enemy != nullptr)
		{
			damageEnemy->Hit(damage + (artifact->WaterPower.atkLevel * 2), knockBack);
		}
	}
	

}


