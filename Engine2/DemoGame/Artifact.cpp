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
	//아티팩트 csv이름이랑 이미지 이름 일치시키기
	Make(Image)(L"Crossbow.png").setPosition({ 100.f * ownArtifact.size() ,100});
}


