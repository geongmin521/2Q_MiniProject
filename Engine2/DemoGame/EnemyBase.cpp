#include "../D2DEngine/pch.h"
#include "EnemyBase.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/D2DRenderer.h"

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
	if (target != nullptr && target->isActive == false)
	{
		target = nullptr;
	}
}

void EnemyBase::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
	int mHp = static_cast<int>(curHP);
	std::wstring hp = std::to_wstring(mHp);
	pRenderTarget->DrawTextW(hp.c_str(), hp.length(), D2DRenderer::GetInstance()->DWriteTextFormat, D2D1::RectF(GetWorldLocation().x - 50, GetWorldLocation().y - 100, GetWorldLocation().x + 50, GetWorldLocation().y),
		D2DRenderer::GetInstance()->Brush);
}


void EnemyBase::Find(Collider* othercomponent)
{
	std::vector<GameObject*> towers;
	for (auto& col : othercomponent->collideStatePrev )
	{
		if (col->owner->name == "Tower" && col->owner->isActive ==true)
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

void EnemyBase::Attack(float deltaTime)
{

}
