#include "pch.h"
#include "TowerFunc.h"
#include "GameObject.h"
#include "Transform.h"
#include "TowerBase.h"
#include "EnemyBase.h"
#include "Arrow.h"
#include "Pools.h"
void TowerFunc::FireBullet(GameObject* target, MathHelper::Vector2F pos,float id) //�Ѿ˵� ���丮�� ��������.. //��������.. ȭ������ �����ؼ���û�� �������ϰ�... //���ݱ��� �ѰŶ� �����ؼ�.. ������ Ŀ�����ؼ� �Ѿ� ������? 
{
	if (target != nullptr)
	{
		Arrow* arrow = dynamic_cast<Arrow*>(Pools::GetInstance().get()->PopPool(id + 500)); //�Ѿ��� ���̵�����ѵ�.. //���⼭ �Ѿ˸� �߰�������ǰ���? 
		arrow->Init(pos, target);
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

void TowerFunc::MeleeAttack(GameObject* my,std::vector<GameObject*>& targets)
{
	for (auto& enemy : targets)
	{		
		EnemyBase* damageEnemy = dynamic_cast<EnemyBase*>(enemy); //Ÿ������ ���������������������ϱ�... �̰͵� �������̽��� ����?
		//���⵵ ���⼭ ��ġ�� ������.. ���ۿ� ��ȯ���� ��������ϱ� ��ƿ�� �����ؼ� �� Ÿ���̶� ���� ������ ����ϸ�ɵ�?
		if (enemy != nullptr)
		{
			MathHelper::Vector2F dir = (enemy->GetWorldLocation() - my->GetWorldLocation()).Normalize();
			damageEnemy->Hit(Utility::CalCul("�Ϲ���", damageEnemy->enemyData.Type, 3),150);  //��Ÿ���� ��Գ��� �ϴ� �ϵ��ڵ� //��������
		}
	}
}
