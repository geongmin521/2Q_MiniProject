#pragma once
//#include "AABB.h"
#include "Component.h" //aabb를갖는애들이많을텐데 다없애자.. 

class AABB;
class CameraScene : public Component
{
public:
	CameraScene();
	virtual ~CameraScene();
	virtual void Update(float deltaTime);
	float moveSpeed;
	AABB* viewBoundBox; //AABB도 어디 한군데다가 몰아놔야하는데.. 

};

