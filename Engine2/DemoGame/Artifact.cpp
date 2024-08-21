#include "pch.h"
#include "Artifact.h"
#include "Factory.h"
#include "Image.h"
#include "Dotween.h"
#include "TowerBase.h"
#include "DataManager.h"
#include "ArtifactObject.h"

Artifact::Artifact()	//��¥ ȭ����.. �̵����� �س��� ���ߴٴ°ǰ�? ������ ���Ѻ��ǰ�? 
{
	//dataManager->CSVReader(L"ArtifactData");
	// csv ���� �� ������ ������
	Init();
}

Artifact::~Artifact()

{
}

void Artifact::SelectArtifact(int id)
{
	ownedArtifact.push_back(id);
	
	levelUp(id);
	Make(ArtifactObject)(id, 25.f * ownedArtifact.size(), 80);

	//��Ƽ��Ʈ csv�̸��̶� �̹��� �̸� ��ġ��Ű��
}
// ������ ���� �ö󰡾����� �𸣰ھ ���� �� ����

void Artifact::Init()
{
	// �ܼ� ���� ������
	levelUpActions[500] = [this]() { WaterPower.increaseAtk(); };
	levelUpActions[501] = [this]() { PilePower.increaseAtk(); };
	levelUpActions[502] = [this]() { BowPower.increaseAtk(); };
	levelUpActions[503] = [this]() { HolyPower.increaseAtk(); };
	levelUpActions[504] = [this]() { WaterPower.increaseHp(); };
	levelUpActions[505] = [this]() { PilePower.increaseHp(); };
	levelUpActions[506] = [this]() { BowPower.increaseHp(); };
	levelUpActions[507] = [this]() { HolyPower.increaseHp(); };
	levelUpActions[508] = [this]() { WaterPower.increaseSpd(); };
	levelUpActions[509] = [this]() { PilePower.increaseSpd(); };
	levelUpActions[510] = [this]() { BowPower.increaseSpd(); };
	levelUpActions[511] = [this]() { HolyPower.increaseSpd(); };
				   
	levelUpActions[514] = [this]() { Range += 100.f; };
	levelUpActions[515] = [this]() { knockback += 15.f; };
}

void Artifact::levelUp(int id)
{
	//std::wstring original = L"Artifact/" + Utility::convertFromString(dataManager->getArtifactData(id).filePath) + L".png";
	//Make(Image)(original).setScale({ 0.5f ,0.5f }).setPosition({ 50.f * ownedArtifact.size() ,100 });

	auto action = levelUpActions.find(id);
	if (action != levelUpActions.end()) 
	{
		action->second();
	}
}

bool Artifact::isOwned(int id)
{
	std::vector<int>::iterator it;
	it = std::find(ownedArtifact.begin(), ownedArtifact.end(), id);
	if (it != ownedArtifact.end())
	{
		return true;
	}
	return false;
}

