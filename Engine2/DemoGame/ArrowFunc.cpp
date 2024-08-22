#include "pch.h"
#include "EnemyBase.h"
#include "TowerBase.h"
#include "CommonFunc.h"
#include "CircleCollider.h"
#include "Circle.h"
#include "Effect.h"
#include "Pools.h"
#include "Arrow.h"
#include "ArrowFunc.h"
#include "Artifact.h"

void ArrowFunc::AttackEnemy(Arrow* my,GameObject* target,std::string type, float damage, float knockBack)
{
	// ���Ŀ� ��Ƽ��Ʈ ������� ������ ������ ����
	EnemyBase* enemy = dynamic_cast<EnemyBase*>(target);	
	MathHelper::Vector2F dir = (enemy->GetWorldLocation() - my->GetWorldLocation()).Normalize();
	enemy->Hit(Utility::CalCul(type, enemy->enemyData.Type, damage + (artifact->CrossbowPower.atkLevel * 2)), knockBack); //�ϴ� 100 �˹��ġ �޾ƿ����ʿ�
	Effect* effect = dynamic_cast<Effect*>(Pools::GetInstance().get()->PopPool(2004+ my->level));
	effect->Init(my->GetWorldLocation(), 0.5f); //����Ʈ ����
	Pools::GetInstance().get()->AddPool(my);
}

void ArrowFunc::AttackTower(GameObject* my, GameObject* target, std::string type, float damage, float knockBack)
{
	// ���Ŀ� ��Ƽ��Ʈ ������� ������ ������ ����
	MathHelper::Vector2F dir = (target->GetWorldLocation() - my->GetWorldLocation()).Normalize();
	IDamageNotify* nofity = dynamic_cast<IDamageNotify*>(target);
	nofity->Hit(damage); //�ϴ� 100 �˹��ġ �޾ƿ����ʿ�
	//Effect* effect = dynamic_cast<Effect*>(Pools::GetInstance().get()->PopPool(2001));
	//effect->Init(my->GetWorldLocation(), 1.0f); //����Ʈ ����
	Pools::GetInstance().get()->AddPool(my);
}
void ArrowFunc::WaterAttack(Arrow* my,CircleCollider& myCol, std::string type, float damage, float knockBack)
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
	
	Effect* effect = dynamic_cast<Effect*>(Pools::GetInstance().get()->PopPool(2007+my->level));
	effect->Init(myCol.owner->GetWorldLocation(), 1.0f); //����Ʈ ����
	myCol.SetCollisionType(CollisionType::NoCollision); 
	Pools::GetInstance().get()->AddPool(myCol.owner);
	
}

void ArrowFunc::HiddenAttack(CircleCollider& myCol,float damage)
{
	Arrow* arrow = dynamic_cast<Arrow*>(Pools::GetInstance().get()->PopPool(513)); //513������ ����ַο�� ����?
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


