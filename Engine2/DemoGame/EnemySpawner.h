#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/DataManager.h"

class Vampire;
class EnemySpawner : public GameObject
{
private:
	float Timer =3.0f;
	float spawnTimer;
	int spawnCount;
	std::map<int,std::vector<WaveData>> waveData; //맵뽑기를 편하게 하기위해 맵의 레벨별로 묶어서 웨이브데이터를 저장하기
public:
	//WaveData waveData;
	EnemyData enemyData;

	Transform* target;
	EnemySpawner();
	~EnemySpawner();

	void CreateEnemy();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
};

