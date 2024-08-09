#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/DataManager.h"

struct  SpawnData
{
	// 생성자 기본 생성자를 그대로 사용
	SpawnData() = default;
	SpawnData(int count, float spawnTime, int id)
		: Count(count), SpawnTime(spawnTime), id(id) {}

	int Count;
	float SpawnTime;
	int id;
};
class Vampire;
class EnemySpawner : public GameObject
{
private:
	int WaveIndex;
	float spawnTimer;
	std::vector<int> spawnPos; //아따 벡터도 참 많구만
	std::vector<SpawnData> curSpawnData;
	std::vector<float> Timer;
	std::map<int,std::vector<WaveData>> waveData; 

	//생성가능한 개수 스폰시간, 스폰 아이디 이 세가지를 묶어야하는데 자료구조만들기 아니다 만들자.. 
public:
	//WaveData waveData;
	EnemyData enemyData;
	
	Transform* target;
	EnemySpawner();
	~EnemySpawner();

	void CreateEnemy(int id);
	void StartWave();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
};

