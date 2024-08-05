#include "../D2DEngine/pch.h"
#include "TowerBase.h"

TowerBase::TowerBase()
{
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
