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
	// �ϴ� id�� count�� ��ȯ
	
}

void Artifact::setArtifact(int id)
{
	if (artifactData.id == id)
	{
		ownArtifact.push_back(artifactData);
	}

}
