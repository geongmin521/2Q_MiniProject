#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/DataManager.h"

struct  SpawnData
{
	// ������ �⺻ �����ڸ� �״�� ���
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
	std::vector<int> spawnPos; //�Ƶ� ���͵� �� ������
	std::vector<SpawnData> curSpawnData;
	std::vector<float> Timer;
	std::map<int,std::vector<WaveData>> waveData; 

	//���������� ���� �����ð�, ���� ���̵� �� �������� ������ϴµ� �ڷᱸ������� �ƴϴ� ������.. 
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

