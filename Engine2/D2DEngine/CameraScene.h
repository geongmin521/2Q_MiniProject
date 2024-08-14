#pragma once
#include "Component.h"

class AABB;
class CameraScene : public Component
{
public:
	CameraScene();
	virtual ~CameraScene();
	virtual void Update(float deltaTime);
	float moveSpeed;
	AABB* viewBoundBox; 
};

