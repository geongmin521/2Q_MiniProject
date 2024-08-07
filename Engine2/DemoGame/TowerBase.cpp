#include "../D2DEngine/pch.h"
#include "TowerBase.h"


TowerBase::TowerBase()
{
	name = "Tower";
}

TowerBase::~TowerBase()
{
}

void TowerBase::Update(float deltaTime)
{
	__super::Update(deltaTime);

	if (target != nullptr && target->isActive == false)  
	{
		target = nullptr;
	}
}

void TowerBase::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}

void TowerBase::FindTarget(Collider* col)
{ 
	// Ÿ�� �ڷ� �Ѿ���� Ÿ�ٿ� �������� �����ʿ�


	std::vector<GameObject*> enemys;
	for (auto& col : col->collideStatePrev)
	{
		if (col->owner->name == "Enemy" && col->owner->isActive == true)
			enemys.push_back(col->owner);
	}
	float min = 1000;
	float curMin;
	float xDistance;
	float yDistance;
	GameObject* curTarget = nullptr;
	if (!enemys.empty())
	{
		for (auto& enemy : enemys)
		{
			//std::cout << " �� ����";
			xDistance = (GetWorldLocation().x - enemy->GetWorldLocation().x);
			//if (xDistance > 0) continue; //�ϴ� Ÿ���ڷΰ��� ���ݸ��ϰ�
			yDistance = std::abs(GetWorldLocation().y - enemy->GetWorldLocation().y);
			curMin = std::min(xDistance, yDistance);

			if (min > curMin)
			{
				min = curMin;
				curTarget = enemy;
			}
		}
	}
	if (curTarget != nullptr)
	{
		target = curTarget;
	}

}

void TowerBase::FindTargets(Collider* col)
{


	std::vector<GameObject*> enemys;
	for (auto& col : col->collideStatePrev)
	{
		if (col->owner->name == "Enemy" && col->owner->isActive == true)
			enemys.push_back(col->owner);
	}
	float min = 1000;
	float curMin;
	float xDistance;
	float yDistance;
	GameObject* curTarget = nullptr;
	if (!enemys.empty())
	{
		for (auto& enemy : enemys)
		{
			//std::cout << " �� ����";
			xDistance = (GetWorldLocation().x - enemy->GetWorldLocation().x);
			//if (xDistance > 0) continue; //�ϴ� Ÿ���ڷΰ��� ���ݸ��ϰ�
			yDistance = std::abs(GetWorldLocation().y - enemy->GetWorldLocation().y);
			curMin = std::min(xDistance, yDistance);

			if (min > curMin)
			{
				min = curMin;
				curTarget = enemy;
			}
		}
	}
	if (curTarget != nullptr)
	{
		target = curTarget;
	}
	targets = enemys; //Ÿ���̾ȹٲ��� ���������� �������޴� Ÿ�ٵ��� ��� �ٲ�����ϴ´�
}

void TowerBase::Attack(float deltaTime)
{
}


