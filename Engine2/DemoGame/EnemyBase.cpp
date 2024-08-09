#include "pch.h"
#include "HPBar.h"
#include "EnemyBase.h"
#include "AABB.h"
#include "Artifact.h"
#include "D2DRenderer.h"

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
	perHP = (curHP / enemyData.HP) * 100;
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
	for (auto& col : othercomponent->collideStatePrev)
	{
		if (col->owner->name == "Tower" && col->owner->isActive == true)
		{
			
				towers.push_back(col->owner);
			
		}
	}

	float min = 1000;
	float curMin;
	MathHelper::Vector2F distance;
	GameObject* curTarget = nullptr;

	if (!towers.empty())
	{
		for (auto& tower : towers)
		{
			distance = MathHelper::Vector2F(GetWorldLocation()) - MathHelper::Vector2F(tower->GetWorldLocation());
			curMin = distance.Length();
			
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

void EnemyBase::Hit(float damage)
{
	float plusAttack = Artifact::GetInstance().get()->towerPower.Attack;
	float Hpdame = curHP - damage * plusAttack;  //예시 변수명 수정등필요
	if (Hpdame <= 0)
	{
		curHP = 0;
	}
	else
	{
		curHP = Hpdame;
	}
}

void EnemyBase::Attack(float deltaTime)
{

}
