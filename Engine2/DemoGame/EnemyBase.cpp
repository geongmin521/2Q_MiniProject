#include "../D2DEngine/pch.h"
#include "EnemyBase.h"

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
