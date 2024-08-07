#include "../D2DEngine/pch.h"
#include "EnemySpawner.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/World.h"
#include "Vampire.h"
#include "VampireBomb.h"

EnemySpawner::EnemySpawner()
{
	// 임시
	// 스폰카운트 50까지만
	waveData.level = 1;
	spawnTimer = 0.1f;

	if (enemyData.id == waveData.id)
	{

	}
}

EnemySpawner::~EnemySpawner()
{

}

void EnemySpawner::CreateEnemy()
{
	Vampire* newVampire = new Vampire();
	
	// 스폰조건 추후에 생각
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> spawnPos(1, 5);
	float posY = static_cast<float>(spawnPos(gen)) * 150;
	static int y = 1;
	y++;
	y = (y % 10) + 2;
	newVampire->transform->SetRelativeLocation({ 2000,  float(y * 50) });
	newVampire->owner = this->owner;
	owner->m_GameObjects.push_back(newVampire);
	if (spawnCount % 3 == 1)
	{
		VampireBomb* newVamBomb = new VampireBomb();
		newVamBomb->transform->SetRelativeLocation({ 2000, float(y * 50) });
		newVamBomb->owner = this->owner;
		owner->m_GameObjects.push_back(newVamBomb);
		spawnCount++;
	}
	
	spawnCount++;
}

void EnemySpawner::Update(float deltaTime)
{
	Timer -= deltaTime;
	if (Timer < 0.f)
	{
		Timer = spawnTimer;
		if (spawnCount < 20)
		{
			CreateEnemy();
		}
		
	}
}

void EnemySpawner::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
}
