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



void TowerBase::FindTarget(Collider* col, bool isTargets)
{
	// Ÿ�� �ڷ� �Ѿ���� Ÿ�ٿ� �������� �����ʿ�


	std::vector<GameObject*> enemys;
	for (auto& col : col->collideStatePrev)
	{
		if (col->owner->name == "Enemy" && col->owner->isActive == true)
		{
			if (std::abs(GetWorldLocation().x - col->owner->GetWorldLocation().x) <= towerData.attackRange &&
				std::abs(GetWorldLocation().y - col->owner->GetWorldLocation().y) <= towerData.attackRange)
			{
				enemys.push_back(col->owner);
			}
		}
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
			xDistance = std::abs(GetWorldLocation().x - enemy->GetWorldLocation().x);
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
	if (isTargets == true)
	{
		this->targets = enemys;
	}
}

void TowerBase::Attack(float deltaTime)
{
}


