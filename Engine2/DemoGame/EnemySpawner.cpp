#include "../D2DEngine/pch.h"
#include "../D2DEngine/Transform.h"
#include "EnemySpawner.h"
#include "Vampire.h"
#include "../D2DEngine/World.h"

EnemySpawner::EnemySpawner()
{
	spawnTimer = 3.f;
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::CreateEnemy()
{
	Vampire* newVampire = new Vampire();

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> spawnPos(1, 5);
	float posY = (float)spawnPos(gen) * 150;
	//newVampire->transform->SetRelativeLocation({ 100.f,  posY });
	newVampire->owner = this->owner;

	owner->m_GameObjects.push_back(newVampire);
}

void EnemySpawner::Update(float deltaTime)
{
	Timer -= deltaTime;
	if (Timer < 0.f)
	{
		Timer = spawnTimer;
		CreateEnemy();
	}
}

void EnemySpawner::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
}
