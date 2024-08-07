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
	// 타워 뒤로 넘어간적은 타겟에 안잡히게 수정필요


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
			//std::cout << " 적 있음";
			xDistance = std::abs(GetWorldLocation().x - enemy->GetWorldLocation().x);
			//if (xDistance > 0) continue; //일단 타워뒤로가면 공격못하게
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


