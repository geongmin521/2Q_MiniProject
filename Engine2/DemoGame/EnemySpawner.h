#pragma once
#include "GameObject.h"

struct  SpawnData
{

	SpawnData(int count, float spawnTime, int id)
		: Count(count), SpawnTime(spawnTime), id(id) {}

	int Count;
	float SpawnTime;
	int id;
};
class EnemySpawner : public GameObject
{
private:
	int WaveIndex;
	float spawnTimer;
	std::vector<int> spawnPos; 
	std::vector<SpawnData> curSpawnData;
	std::vector<float> Timer;
public:
	EnemySpawner();
	~EnemySpawner();
	void CreateEnemy(int id);
	void StartWave();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha =1) override;
};

