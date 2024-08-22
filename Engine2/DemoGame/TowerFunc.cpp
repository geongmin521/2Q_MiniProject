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
		my->cooldown = my->curSpeed;  //���Ÿ�Ÿ�� ������ �������� �ٷ� �ٽ� �����ϰ��ش޷��� �߰�
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
			effect->Init(tower->GetWorldLocation(), 0.25f); //����Ʈ ����
		}
	}
}

void TowerFunc::MeleeAttack(GameObject* my,std::vector<GameObject*>& targets)
{
	TowerBase* myTower = dynamic_cast<TowerBase*>(my);
	// ���Ŀ� ��Ƽ��Ʈ ������� ������ ������ ����
		
	for (auto& enemy : targets)
	{		
		EnemyBase* damageEnemy = dynamic_cast<EnemyBase*>(enemy);
		if (enemy != nullptr)
		{			
			damageEnemy->Hit(Utility::CalCul(myTower->towerData.Type, damageEnemy->enemyData.Type, myTower->towerData.ATK + (artifact->PilePower.atkLevel * 2)), myTower->knockBack);
		}
	}
}
