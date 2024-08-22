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

	float MaxDelayTime = 3.0f; // 용도 대사 하고선 딜레이 타임
	float TimeSave = 0;


	// 이렇게 2개 세트
	void BossAwake(float deltaTime);
	void ResetPos();

	void Earthquake();
private:
	void ReseEarthquake();
};

