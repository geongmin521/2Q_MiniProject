#include "../D2DEngine/pch.h"
#include "TowerBase.h"
#include "../D2DEngine/D2DRenderer.h"


TowerBase::TowerBase(TowerData data)
{
	name = "Tower";
	this->towerData = data;	
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
	int mHp = static_cast<int>(curHP);
	std::wstring hp = std::to_wstring(mHp);
	pRenderTarget->DrawTextW(hp.c_str(), hp.length(), D2DRenderer::GetInstance()->DWriteTextFormat, D2D1::RectF(GetWorldLocation().x - 50, GetWorldLocation().y - 100, GetWorldLocation().x + 50, GetWorldLocation().y),
		D2DRenderer::GetInstance()->Brush);
}



void TowerBase::FindTarget(Collider* col, bool isTargets,bool isHeal)
{
	// 타워 뒤로 넘어간적은 타겟에 안잡히게 수정필요


	std::vector<GameObject*> enemys;

	if(isHeal == false)
	{
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
	}
	else
	{
		for (auto& col : col->collideStatePrev)
		{
			if (col->owner->isActive == true)
			{
				if (std::abs(GetWorldLocation().x - col->owner->GetWorldLocation().x) <= towerData.attackRange &&
					std::abs(GetWorldLocation().y - col->owner->GetWorldLocation().y) <= towerData.attackRange)
				{
					enemys.push_back(col->owner);
				}
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

void TowerBase::Hit(float damage)
{

	curHP -= damage;
}

void TowerBase::Heal(float heal)
{
	float healHP = curHP;
	healHP += heal;
	if (healHP >= towerData.HP)
		curHP = towerData.HP;
	else
		curHP += heal;
}


