#include "../D2DEngine/pch.h"
#include "EnemySpawner.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/World.h"
#include "Vampire.h"
#include "VampireBomb.h"

EnemySpawner::EnemySpawner()
{
	// �ӽ�
	// ����ī��Ʈ 50������
	waveData.level = 1;
	spawnTimer = 3.f;

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
	//VampireBomb* newVamBomb = new VampireBomb();
	// �������� ���Ŀ� ����
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> spawnPos(1, 5);
	float posY = (float)spawnPos(gen) * 150;
	newVampire->transform->SetRelativeLocation({ 2000,  100 });
	newVampire->owner = this->owner;

	owner->m_GameObjects.push_back(newVampire);
	spawnCount++;
}

void EnemySpawner::Update(float deltaTime)
{
	Timer -= deltaTime;
	if (Timer < 0.f)
	{
		Timer = spawnTimer;
		if (spawnCount < 1)
		{
			CreateEnemy();
		}
		
	}
}

void EnemySpawner::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
}
