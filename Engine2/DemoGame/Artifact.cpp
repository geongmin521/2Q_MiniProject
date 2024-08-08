#include "../D2DEngine/pch.h"
#include "Artifact.h"
#include "../D2DEngine/GameObject.h"

Artifact::Artifact()
{
	//DataManager::GetInstance().get()->CSVReader(L"ArtifactData");
}

Artifact::~Artifact()
{
}

int Artifact::getArtifact()
{
	// 일단 id랑 count만 반환
	
}

void Artifact::setArtifact(int id)
{
	if (artifactData.id == id)
	{
		ownArtifact.push_back(artifactData);
	}

}
