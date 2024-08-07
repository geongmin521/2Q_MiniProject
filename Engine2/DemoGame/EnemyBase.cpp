#include "../D2DEngine/pch.h"
#include "EnemyBase.h"
#include "../D2DEngine/AABB.h"
EnemyBase::EnemyBase()
{
	name = "Enemy";
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update(float deltaTime)
{
	__super::Update(deltaTime);
}

void EnemyBase::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}


void EnemyBase::Find(Collider* othercomponent)
{
	std::vector<GameObject*> towers;
	for (auto& col : othercomponent->collideStatePrev)
	{
		if (col->owner->name == "Tower")
		{
			towers.push_back(col->owner);
		}
	}

	float min = 1000;
	float curMin;
	float xDistance;
	float yDistance;
	GameObject* curTarget = nullptr;

	if (!towers.empty())
	{
		for (auto& tower : towers)
		{
			xDistance = std::abs((GetWorldLocation().x - tower->GetWorldLocation().x));
			yDistance = std::abs(GetWorldLocation().y - tower->GetWorldLocation().y);
			curMin = std::min(xDistance, yDistance);

			if (min > curMin)
			{
				min = curMin;
				curTarget = tower;
			}

		}
	}

	if (curTarget != nullptr)
	{
		target = curTarget;
	}	
}