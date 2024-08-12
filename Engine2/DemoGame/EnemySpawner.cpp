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
	//�̰� ����ȯ �Ͼ���ϸ� �ȵǳ�?
	Pools::GetInstance().get()->PopPool(id)->transform->SetRelativeLocation({(float)2000,(float)spawnPos[pos]}); //����� ���̵�� ó���Ұǵ�. Ǯ�� �̸��̰�.. ��ȯ�⸦ �ϳ� �����? 
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

void EnemySpawner::Update(float deltaTime) //�����ʰ� �ִ� 4���ϼ������ϱ�.. ���ͷ� �־����.. 
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
