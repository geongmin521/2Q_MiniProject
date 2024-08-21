#pragma once
#include "GameObject.h"
class ArtifactObject : public GameObject
{
public:
	
	ArtifactObject(int id, float targetPosX, float targetPosY);
	virtual ~ArtifactObject();
};

