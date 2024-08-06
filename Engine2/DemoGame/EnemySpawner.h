#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/DataManager.h"

class Vampire;
class EnemySpawner : public GameObject
{
private:
	float Timer =3.0f;
	float spawnTimer;
public:
	WaveData waveData;

	Transform* target;
	EnemySpawner();
	~EnemySpawner();

	void CreateEnemy();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
};

