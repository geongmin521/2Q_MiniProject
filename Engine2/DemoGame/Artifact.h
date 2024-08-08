#pragma once
#include "../D2DEngine/SingletonBase.h"
#include "../D2DEngine/DataManager.h"

class GameObject;
class Artifact : public SingletonBase<Artifact>
{
public:
	Artifact();
	virtual ~Artifact();

	int getArtifact();

	void setArtifact(int id);

	ArtifactData artifactData;

	std::vector<ArtifactData> ownArtifact;
};

