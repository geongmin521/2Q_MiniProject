#include "pch.h"
#include "Artifact.h"
#include "Factory.h"
#include "Image.h"
#include "TowerBase.h"
#include "DataManager.h"

Artifact::Artifact()//��¥ ȭ����.. �̵����� �س��� ���ߴٴ°ǰ�? ������ ���Ѻ��ǰ�? 
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
	//��Ƽ��Ʈ csv�̸��̶� �̹��� �̸� ��ġ��Ű��
}
int Artifact::bibleGold(int gold)
{
	if (isOwned(14))
	{
		return gold = gold + (gold * 0.3);
	}
	return gold;
}
// ������ ���� �ö󰡾����� �𸣰ھ ���� �� ����


void Artifact::Init()
{
	// �ܼ� ���� ������
	levelUpActions[1] = [this]() { WaterPower.increaseAtk(); };
	levelUpActions[2] = [this]() { PilePower.increaseAtk(); };
	levelUpActions[3] = [this]() { BowPower.increaseAtk(); };
	levelUpActions[4] = [this]() { HolyPower.increaseAtk(); };
	levelUpActions[5] = [this]() { WaterPower.increaseHp(); };
	levelUpActions[6] = [this]() { PilePower.increaseHp(); };
	levelUpActions[7] = [this]() { BowPower.increaseHp(); };
	levelUpActions[8] = [this]() { HolyPower.increaseHp(); };
	levelUpActions[9] = [this]() { WaterPower.increaseSpd(); };
	levelUpActions[10] = [this]() { PilePower.increaseSpd(); };
	levelUpActions[11] = [this]() { BowPower.increaseSpd(); };
	levelUpActions[12] = [this]() { HolyPower.increaseSpd(); };

	levelUpActions[15] = [this]() { Range += 100.f; };
	levelUpActions[16] = [this]() { knockback += 15.f; };
}

void Artifact::levelUp(int id)
{
	std::wstring original = L"Artifact/" + Utility::convertFromString(dataManager->getArtifactData(id).filePath) + L".png";
	Make(Image)(original).setScale({ 0.5f ,0.5f }).setPosition({ 50.f * ownedArtifact.size() ,100 });

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

