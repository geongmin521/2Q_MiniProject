#include "pch.h"
#include "EnemySpawner.h"
#include "Transform.h"
#include "World.h"
#include "Pools.h"
#include "DataManager.h"
#include "GameManager.h"
#include "Vampire.h"
#include "VampireBomb.h"

EnemySpawner::EnemySpawner()
{
	std::variant<std::vector<EnemyData>, std::vector<TowerData>, std::vector<WaveData>, std::vector<ArtifactData>> data =
		DataManager::GetInstance().get()->CSVReader(L"WaveData");

	if (std::holds_alternative<std::vector<WaveData>>(data)) { //처음 웨이브 데이터 읽기.. 
		for (auto var : std::get<std::vector<WaveData>>(data))
			waveData[var.level].push_back(var);
	}

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

void EnemySpawner::StartWave() //원래는 웨이브시작할때 뽑는게 아니라 그전에 뽑아서 보여주고 전투가 시작되면 그때 보여줘야함. 
{
	WaveIndex = Utility::RandomBetween(0, waveData[gameManager->WaveLevel].size() - 1);
	WaveData data = waveData[gameManager->WaveLevel][WaveIndex];
	//원본데이터는 유지하고 현재 변경될 값들을 넣어주기
	for (int i = 0; i < data.enemyId.size(); i++)
	{
		Timer.push_back(data.spawnTime[i]);
		curSpawnData.push_back({ data.enemyCount[i],data.spawnTime[i], data.enemyId[i] });
	}
	
	//저장할때를 저 구조체로 담았으면 훨씬 편했을텐데 나중에 수정하는걸로하자.. //흠 아닌가? 맞나? 확인해보면되지.. 
	
	
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
