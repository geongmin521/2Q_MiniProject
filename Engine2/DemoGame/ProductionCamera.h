#pragma once
#include "GameObject.h"

class ProductionCamera : public GameObject
{
public:
	ProductionCamera();
	virtual ~ProductionCamera() = default;

	virtual void Update(float deltaTime);

	float speed = 10.f;

	bool istest = false;
	bool isEarthquake = false;

	bool isDialogueDelay = false;
	bool isBattleBegins = false;

	float EarthquakeTime = 0;
	float BossAwakeTime = 0.f;

	float MaxDelayTime = 3.0f; // �뵵 ��� �ϰ� ������ Ÿ��
	float TimeSave = 0;


	// �̷��� 2�� ��Ʈ
	void BossAwake(float deltaTime);
	void ResetPos();

	void Earthquake();
private:
	void ReseEarthquake();
};

