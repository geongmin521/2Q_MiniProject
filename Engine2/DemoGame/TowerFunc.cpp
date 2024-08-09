#include "pch.h"
#include "TowerFunc.h"
#include "CircleCollider.h"
#include "GameObject.h"
#include "circle.h"
#include "Transform.h"
#include "TowerBase.h"
#include "EnemyBase.h"
#include "Pools.h"

 void TowerFunc::FindTarget(CircleCollider& myCol,std::string tag, std::vector<GameObject*>& target) //���� Ÿ�� �˻�
{
	target.clear();
	GameObject* enemy = nullptr;
	
	int minDistance = INT_MAX;
	for (auto& tragetCol : myCol.collideStatePrev) //�ݶ��̴��� ���������ϰŰ�.. �ű⿡ ���Դٸ�.. �׳� ���߿��� ���� �����͸� ã�����
	{
		if (tragetCol->owner->name != tag || tragetCol->owner->isActive != true)
			continue;

		float distance = myCol.circle->GetDistance(tragetCol->owner->transform->GetWorldLocation());
		if (distance < minDistance)
		{
			minDistance = distance;
			enemy = tragetCol->owner;
		}
	}
	target.push_back(enemy);
}
 
void TowerFunc::FindTargets(CircleCollider& myCol, std::string tag, std::vector<GameObject*>& targets) //���� Ÿ�� �˻��ϱ�
{

	targets.clear();
	for (auto& tragetCol : myCol.collideStatePrev) //�ݶ��̴��� ���������ϰŰ�.. �ű⿡ ���Դٸ�.. �׳� ���߿��� ���� �����͸� ã�����
	{
		if (tragetCol->owner->name != tag || tragetCol->owner->isActive != true)
			continue;
		targets.push_back(tragetCol->owner);
	}
}

void TowerFunc::FireBullet(GameObject* target) //�Ѿ˵� ���丮�� ��������.. //��������.. ȭ������ �����ؼ���û�� �������ϰ�... //���ݱ��� �ѰŶ� �����ؼ�.. ������ Ŀ�����ؼ� �Ѿ� ������? 
{
	if (target != nullptr)
	{
		Pools::GetInstance().get()->PopPool(500); //�Ѿ��� ���̵�����ѵ�.. 
	}
}

void TowerFunc::Heal(std::vector<GameObject*>& targets) //���ӿ�����Ʈ�� ���͸� �����ͼ� �̸����� ����ϱ�.. //������ �±׷� �� Ÿ���� �� ã�����״ϱ�. 
{
	for (auto& tower : targets)
	{
		TowerBase* healTower = dynamic_cast<TowerBase*>(tower); //Ÿ������ ���������������������ϱ�... �̰͵� �������̽��� ����?
		if(tower != nullptr) 
			healTower->Heal(1000);
	}
}

void TowerFunc::MeleeAttack(std::vector<GameObject*>& targets)
{
	for (auto& enemy : targets)
	{		
		EnemyBase* damageEnemy = dynamic_cast<EnemyBase*>(enemy); //Ÿ������ ���������������������ϱ�... �̰͵� �������̽��� ����?
		//���⵵ ���⼭ ��ġ�� ������.. ���ۿ� ��ȯ���� ��������ϱ� ��ƿ�� �����ؼ� �� Ÿ���̶� ���� ������ ����ϸ�ɵ�?
		if (enemy != nullptr)
			damageEnemy->Hit(1000);
	}
}
