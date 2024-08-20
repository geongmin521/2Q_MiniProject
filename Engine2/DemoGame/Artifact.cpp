#include "pch.h"
#include "Artifact.h"
#include "Factory.h"
#include "Image.h"
#include "TowerBase.h"

Artifact::Artifact()
{
	//dataManager->CSVReader(L"ArtifactData");
	// csv 없음 값 강제로 대입함
	Init();
}

Artifact::~Artifact()

{
}

void Artifact::SelectArtifact(int id)
{
	ownedArtifact.push_back(id);
	levelUp(id);
	//아티팩트 csv이름이랑 이미지 이름 일치시키기
}
int Artifact::bibleGold(int gold)
{
	if (isOwned(14))
	{
		return gold = gold + (gold * 0.3);
	}
	return gold;
	
}
// 스탯이 언제 올라가야할지 모르겠어서 고정 값 대입


void Artifact::Init()
{
	// 단순 스탯 증가만
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
	std::wstring original = L"Artifact/" + artifactIdToString(id) + L".png";
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

std::wstring artifactIdToString(int id)
{
	switch (id) {
	case 1:
	case 5:
	case 9:
		return L"Water";
	case 2:
	case 6:
	case 10:
		return L"Pile";
	case 3:
	case 7:
	case 11:
		return L"Bow";
	case 4:
	case 8:
	case 12:
		return L"Holy";
	case 13:
		return L"Garlic";
	case 14:
		return L"Bible";
	case 15:
		return L"SilverRing";
	case 16:
		return L"Laurel";
	case 17:
		return L"Wine";
	case 18:
		return L"Mirror";
	}
}
