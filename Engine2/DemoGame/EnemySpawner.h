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
	std::map<int,std::vector<WaveData>> waveData; //�ʻ̱⸦ ���ϰ� �ϱ����� ���� �������� ��� ���̺굥���͸� �����ϱ�
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

