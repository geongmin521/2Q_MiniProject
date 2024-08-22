#include "pch.h"
#include "TowerFunc.h"
#include "GameObject.h"
#include "Transform.h"
#include "TowerBase.h"
#include "EnemyBase.h"
#include "Arrow.h"
#include "Effect.h"
#include "Pools.h"
#include "Artifact.h"

void TowerFunc::FireBullet(TowerBase* my,GameObject* target, MathHelper::Vector2F pos,float id) 
{
	if (target != nullptr)
	{
		Arrow* arrow = dynamic_cast<Arrow*>(Pools::GetInstance().get()->PopPool(id + 500));
		arrow->Init(pos, target,my->towerData.level);
	}
	else
	{
		my->cooldown = my->curSpeed;  //원거리타워 공격중 적죽으면 바로 다시 공격하게해달래서 추가
	}
}

void TowerFunc::Heal(GameObject* my, std::vector<GameObject*>& targets)
{
	TowerBase* myTower = dynamic_cast<TowerBase*>(my);
	for (auto& tower : targets)
	{
		TowerBase* healTower = dynamic_cast<TowerBase*>(tower);
		if (healTower != nullptr)
		{
			healTower->Heal(myTower->towerData.ATK + (artifact->HolyPower.atkLevel * 5));
			Effect* effect = dynamic_cast<Effect*>(Pools::GetInstance().get()->PopPool(2004));
			effect->Init(tower->GetWorldLocation(), 0.25f); //이펙트 생성
		}
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
			damageEnemy->Hit(Utility::CalCul(myTower->towerData.Type, damageEnemy->enemyData.Type, myTower->towerData.ATK + (artifact->PilePower.atkLevel * 2)), myTower->knockBack);
		}
	}
}
