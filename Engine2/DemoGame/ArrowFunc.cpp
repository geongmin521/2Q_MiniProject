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
	EnemyBase* enemy = dynamic_cast<EnemyBase*>(target);	//���������� ����ġ�� ����Ʈ����� 
	enemy->Hit(Utility::CalCul(type, enemy->enemyData.Type, damage));
}

void ArrowFunc::AttackEnemys(CircleCollider& myCol, std::string type, float damage)
{
	//�����׸����� �ٲٰ� �����ִϸ��̼�? �̳� �ణ�� ������ �Ŀ� ������Բ� �ؾ��ϴ´�
	std::vector<GameObject*> targets;
	CommonFunc::FindTargets(myCol, "Enemy", targets, myCol.circle->radius);  
	for (auto& enemy : targets)
	{
		EnemyBase* damageEnemy = dynamic_cast<EnemyBase*>(enemy);
		if (enemy != nullptr)
			damageEnemy->Hit(Utility::CalCul(type, damageEnemy->enemyData.Type, damage)); //�������� �Ű������� Ÿ���������� �޾ƿ��Բ��ϰ�
	}
	Effect* effect = dynamic_cast<Effect*>(Pools::GetInstance().get()->PopPool(2000));
	effect->Init(L"Example.png", myCol.owner->GetWorldLocation(), 0.3f); //����Ʈ ����
	myCol.SetCollisionType(CollisionType::NoCollision); //�ѹ� ������ ���ݸ���
	
	
}
