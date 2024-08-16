#include "pch.h"
#include "EnemySpawner.h"
#include "Transform.h"
#include "World.h"
#include "Pools.h"
#include "DataManager.h"
#include "GameManager.h"
#include "EnemyBase.h"

EnemySpawner::EnemySpawner()
{
	for (int i = 0; i < 3; i++)
	{
		spawnPos.push_back(350 + i * 150);
	}
	gameManager->events[Event::SpawnEnemy] = [this]() { StartWave(); };
}

EnemySpawner::~EnemySpawner()
{

}

void EnemySpawner::CreateEnemy(int id)
{
	int pos = Utility::RandomBetween(0, spawnPos.size()-1);
	EnemyBase* enemy = dynamic_cast<EnemyBase*>(Pools::GetInstance().get()->PopPool(id));
	enemy->transform->SetRelativeLocation({ (float)2000,(float)spawnPos[pos] });
	enemy->curHP = enemy->enemyData.HP * WavePower; //여기서 체력 초기화해주기.. 지금까지는 어떻게 되고있던거지?
	enemy->curATK = enemy->enemyData.ATK * WavePower; //여기서 체력 초기화해주기.. 지금까지는 어떻게 되고있던거지?
	//웨이브 파워만 가져오고싶은데.. 
}

void EnemySpawner::StartWave() 
{
	WaveData data = dataManager->getWaveData(gameManager->curWaveId);
	WavePower = data.levelPower;
	for (int i = 0; i < data.enemyId.size(); i++)
	{
		Timer.push_back(data.spawnTime[i]);
		gameManager->LiveEenmy += data.enemyCount[i];
		curSpawnData.push_back({ data.enemyCount[i],data.spawnTime[i], data.enemyId[i] });
	}
	
	gameManager->isBattle = true;
}

void EnemySpawner::Update(float deltaTime)
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

void EnemySpawner::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
}
