#include "pch.h"
#include "TowerFunc.h"
#include "GameObject.h"
#include "Transform.h"
#include "TowerBase.h"
#include "EnemyBase.h"
#include "Arrow.h"
#include "Pools.h"
#include "Artifact.h"

void TowerFunc::FireBullet(GameObject* target, MathHelper::Vector2F pos,float id) 
{
	if (target != nullptr)
	{
		Arrow* arrow = dynamic_cast<Arrow*>(Pools::GetInstance().get()->PopPool(id + 500));
		arrow->Init(pos, target);
	}
}

void TowerFunc::Heal(std::vector<GameObject*>& targets) 
{
	for (auto& tower : targets)
	{
		TowerBase* healTower = dynamic_cast<TowerBase*>(tower);
		if(healTower != nullptr)
			healTower->Heal(1000 + (artifact->HolyPower.atkLevel * 5));
	}
}

void TowerFunc::MeleeAttack(GameObject* my,std::vector<GameObject*>& targets)
{
	TowerBase* myTower = dynamic_cast<TowerBase*>(my);
	// 추후에 아티팩트 기반으로 데미지 고정값 증가
	for (auto& enemy : targets)
	{		
		EnemyBase* damageEnemy = dynamic_cast<EnemyBase*>(enemy);
		if (enemy != nullptr)
		{
			damageEnemy->Hit(Utility::CalCul(myTower->towerData.Type, damageEnemy->enemyData.Type, myTower->towerData.ATK + (artifact->PilePower.atkLevel * 2)), myTower->towerData.knockBack);
		}
	}
}
