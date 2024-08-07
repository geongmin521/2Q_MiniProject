#include "../D2DEngine/pch.h"
#include "EnemyBase.h"

EnemyBase::EnemyBase(EnemyData data)
{
	this->enemyData = data;
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

void EnemyBase::ExploreTarget(EnemyBase* enemy, std::vector<GameObject*>& objs)
{
	float min = 1000;
	float curMin;
	float xDistance;
	float yDistance;
	GameObject* curTarget = nullptr;

	for (auto& obj : objs)
	{
		xDistance = (enemy->GetWorldLocation().x - obj->GetWorldLocation().x);
		yDistance = std::abs(enemy->GetWorldLocation().y - obj->GetWorldLocation().y);
		curMin = std::min(xDistance, yDistance);

		if (min > curMin)
		{
			min = curMin;
		}

		curTarget = obj;
	}
	if (curTarget != nullptr)
	{
		target = curTarget;
	}

}
