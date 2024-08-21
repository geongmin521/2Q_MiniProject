#include "pch.h"
#include "Artifact.h"
#include "Factory.h"
#include "Image.h"
#include "Dotween.h"
#include "TowerBase.h"
#include "DataManager.h"
#include "ArtifactObject.h"

Artifact::Artifact()	//진짜 화나네.. 이따구로 해놓고 다했다는건가? 적용은 시켜본건가? 
{						// 죄송합니다
	//dataManager->CSVReader(L"ArtifactData");
	// csv 없음 값 강제로 대입함
	Init();
}

Artifact::~Artifact()

{
}

void Artifact::SelectArtifact(int id)
{
	levelUp(id);
	if(id >= 512)
	{ 
		ownedArtifact.push_back(id);
		Make(ArtifactObject)(id, 60.f * ownedArtifact.size(), 80);
	}
	//아티팩트 csv이름이랑 이미지 이름 일치시키기
}
// 스탯이 언제 올라가야할지 모르겠어서 고정 값 대입

void Artifact::Init()
{
	// 단순 스탯 증가만
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
	
}

void Artifact::levelUp(int id)
{
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

