#include "../D2DEngine/pch.h"
#include "EnemySpawner.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/World.h"
#include "../D2DEngine/Pools.h"
#include "../D2DEngine/DataManager.h"
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
}

EnemySpawner::~EnemySpawner()
{

}

void EnemySpawner::CreateEnemy()
{
	//스폰데이터를 읽어야함.. 
	//Pools::GetInstance().get()->PopPool(); //여기서 값 빼기.. 
	//몬스터의 종류마다 타이머가 하나씩있고.. 생성하기.. 
	//아이디로 받아서 생성하기.. 아이디가 전부 달라야하지않을까?? 
	
	//VampireBomb* newVamBomb = new VampireBomb();
	// 스폰조건 추후에 생각
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> spawnPos(1, 5);
	float posY = (float)spawnPos(gen) * 150;
	Vampire* newVampire = new Vampire(enemyData);
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
		if (spawnCount < 2)
		{
			CreateEnemy();
		}
		
	}
}

void EnemySpawner::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
}
