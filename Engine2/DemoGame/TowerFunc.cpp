#include "pch.h"
#include "TowerFunc.h"
#include "GameObject.h"
#include "Transform.h"
#include "TowerBase.h"
#include "EnemyBase.h"
#include "Arrow.h"
#include "Pools.h"

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
		if(tower != nullptr) 
			healTower->Heal(1000);
	}
}

void TowerFunc::MeleeAttack(GameObject* my,std::vector<GameObject*>& targets)
{
	// ���Ŀ� ��Ƽ��Ʈ ������� ������ ������ ����
	for (auto& enemy : targets)
	{		
		EnemyBase* damageEnemy = dynamic_cast<EnemyBase*>(enemy);
		if (enemy != nullptr)
		{
			damageEnemy->Hit(Utility::CalCul("�Ϲ���", damageEnemy->enemyData.Type, 3),150); 
		}
	}
}
