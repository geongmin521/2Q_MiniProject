#include "pch.h"
#include "Artifact.h"
#include "Factory.h"
#include "Image.h"

Artifact::Artifact()
{
	//dataManager->CSVReader(L"ArtifactData");
}

Artifact::~Artifact()
{
}

void Artifact::SelectAtrifact(int id)
{
	ownArtifact.push_back((ArtifactId)id);
	//��Ƽ��Ʈ csv�̸��̶� �̹��� �̸� ��ġ��Ű��
	Make(Image)(L"Crossbow.png").setPosition({ 100.f * ownArtifact.size() ,100});
}


