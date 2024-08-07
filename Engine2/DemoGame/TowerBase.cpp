#include "../D2DEngine/pch.h"
#include "TowerBase.h"


TowerBase::TowerBase(TowerData data)
{
	this->towerData = data;
}

TowerBase::~TowerBase()
{
}

void TowerBase::Update(float deltaTime)
{
	__super::Update(deltaTime);
}

void TowerBase::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}

void TowerBase::Attack(float deltaTime)
{
}

void TowerBase::ExploreTarget(TowerBase* tower,std::vector<GameObject*>& objs)
{
	float min = 1000;
	float curMin;
	float xDistance;
	float yDistance;
	GameObject* curTarget = nullptr;
	for (auto& obj : objs)
	{
		
		xDistance = (tower->GetWorldLocation().x - obj->GetWorldLocation().x);
		if (xDistance > 0) continue; //일단 타워뒤로가면 공격못하게
		yDistance = std::abs(tower->GetWorldLocation().y - obj->GetWorldLocation().y);
		curMin = std::min(xDistance, yDistance);

		if (min > curMin)
		min = curMin;

		curTarget = obj;
	}
	if(curTarget != nullptr)
	target = curTarget;
}
