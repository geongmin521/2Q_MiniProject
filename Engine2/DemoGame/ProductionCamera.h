#pragma once
#include "GameObject.h"

class ProductionCamera : public GameObject
{
public:
	ProductionCamera();
	virtual ~ProductionCamera() = default;

	virtual void Update(float deltaTime);

	bool isEarthquake = false;
	float EarthquakeTime = 0;

	// �̷��� 2�� ��Ʈ
	void BossAwake();
	void ResetPos();

	void Earthquake();

private:
	void ReseEarthquake();
};

