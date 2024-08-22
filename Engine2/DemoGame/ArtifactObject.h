#pragma once
#include "GameObject.h"
#include "IOnMouse.h"
class ArtifactData;
class ArtifactObject : public GameObject, public IOnMouse
{
public:
	ArtifactData* data;
	ArtifactObject(int id, float targetPosX, float targetPosY);
	virtual ~ArtifactObject();
	virtual void OnMouse() override;
	virtual void OutMouse() override;
};

