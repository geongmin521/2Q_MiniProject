#pragma once
#include "GameObject.h"

class ProductionCamera : public GameObject
{
public:
	ProductionCamera();
	virtual ~ProductionCamera() = default;

	virtual void Update(float deltaTime);

	void BossAwake();
	void ResetPos();
};

