#include "pch.h"
#include "TowerFunc.h"
#include "CircleCollider.h"
#include "GameObject.h"
#include "circle.h"
#include "Transform.h"
#include "TowerBase.h"
#include "EnemyBase.h"
#include "Arrow.h"
#include "Pools.h"

 void TowerFunc::FindTarget(CircleCollider& myCol,std::string tag, std::vector<GameObject*>& target) //���� Ÿ�� �˻�
{
	target.clear();
	GameObject* enemy = nullptr;
	
	TowerBase* myTower = dynamic_cast<TowerBase*>(myCol.owner);
	int minDistance = INT_MAX;
	for (auto& tragetCol : myCol.collideStatePrev) //�ݶ��̴��� ���������ϰŰ�.. �ű⿡ ���Դٸ�.. �׳� ���߿��� ���� �����͸� ã�����
	{
		if (tragetCol->owner->name == tag && tragetCol->owner->isActive == true)
		{
			float distance = (myTower->GetWorldLocation() - tragetCol->owner->GetWorldLocation()).
			if (!(std::abs() <= myTower->towerData.attackRange * 50) //50���ϴ°� ���� ���߿� csv���� ��ĭ���� ����?
				|| !(std::abs(myTower->GetWorldLocation().y - tragetCol->owner->GetWorldLocation().y) <= myTower->towerData.attackRange * 50))
				continue;      //�� ��ü��ġ�� ��Ÿ����̸� �Ѿ��  �̷��Ը³�?
			float distance = myCol.circle->GetDistance(tragetCol->owner->transform->GetWorldLocation());
			if (distance < minDistance)
			{
				minDistance = distance;
				enemy = tragetCol->owner;
			}
		}			
	}
	if(enemy != nullptr)
		target.push_back(enemy);
}
 
void TowerFunc::FindTargets(CircleCollider& myCol, std::string tag, std::vector<GameObject*>& targets) //���� Ÿ�� �˻��ϱ�
{
	targets.clear();
	TowerBase* myTower = dynamic_cast<TowerBase*>(myCol.owner);
	for (auto& tragetCol : myCol.collideStatePrev) //�ݶ��̴��� ���������ϰŰ�.. �ű⿡ ���Դٸ�.. �׳� ���߿��� ���� �����͸� ã�����
	{
		
		if (tragetCol->owner->name == tag && tragetCol->owner->isActive == true)
		{
			if (!(std::abs(myTower->GetWorldLocation().x - tragetCol->owner->GetWorldLocation().x) <= myTower->towerData.attackRange * 50) //50���ϴ°� ���� ���߿� csv���� ��ĭ���� ����?
				||!(std::abs(myTower->GetWorldLocation().y - tragetCol->owner->GetWorldLocation().y) <= myTower->towerData.attackRange * 50))
				continue;      //�� ��ü��ġ�� ��Ÿ����̸� �Ѿ��  �̷��Ը³�?
			targets.push_back(tragetCol->owner);
		}
	}
}

void TowerFunc::FireBullet(GameObject* target, Vector2F pos) //�Ѿ˵� ���丮�� ��������.. //��������.. ȭ������ �����ؼ���û�� �������ϰ�... //���ݱ��� �ѰŶ� �����ؼ�.. ������ Ŀ�����ؼ� �Ѿ� ������? 
{
	if (target != nullptr)
	{
		Arrow* arrow = dynamic_cast<Arrow*>(Pools::GetInstance().get()->PopPool(500)); //�Ѿ��� ���̵�����ѵ�.. //���⼭ �Ѿ˸� �߰�������ǰ���? 
		arrow->Init(target, pos);
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
			damageEnemy->Hit(40);
	}
}
