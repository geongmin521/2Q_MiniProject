#include "pch.h"
#include "EnemySpawner.h"
#include "Transform.h"
#include "World.h"
#include "Pools.h"
#include "DataManager.h"
#include "GameManager.h"

EnemySpawner::EnemySpawner()
{
	for (int i = 0; i < 5; i++)
	{
		spawnPos.push_back(200 + i * 150);
	}
}

EnemySpawner::~EnemySpawner()
{

}

void EnemySpawner::CreateEnemy(int id)
{
	int pos = Utility::RandomBetween(0, spawnPos.size()-1);
	//이거 형변환 일어나게하면 안되나?
	Pools::GetInstance().get()->PopPool(id)->transform->SetRelativeLocation({(float)2000,(float)spawnPos[pos]}); //여기는 아이디로 처리할건데. 풀은 이름이고.. 변환기를 하나 만들까? 
}

void EnemySpawner::StartWave() 
{
	WaveData data = DataManager::GetInstance().get()->getWaveData(gameManager->WaveLevel);

	for (int i = 0; i < data.enemyId.size(); i++)
	{
		Timer.push_back(data.spawnTime[i]);
		curSpawnData.push_back({ data.enemyCount[i],data.spawnTime[i], data.enemyId[i] });
	}
	
	gameManager->isBattle = true;
}

void EnemySpawner::Update(float deltaTime) //스포너가 최대 4개일수있으니까.. 벡터로 넣어서하자.. 
{
	if (gameManager->isBattle == false)
		return;
	
	for (int i = 0; i < curSpawnData.size(); i++)
	{
		Timer[i] -= deltaTime;
		if (Timer[i] < 0&& curSpawnData[i].Count > 0)
		{
			curSpawnData[i].Count--;
			Timer[i] = curSpawnData[i].SpawnTime;
			CreateEnemy(curSpawnData[i].id);
		}
	}
}

void EnemySpawner::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
}
