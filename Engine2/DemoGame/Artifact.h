#pragma once
#include "SingletonBase.h"
#include "Data.h"

class TowerBase;
enum class ArtifactId
{
	WaterDamageUp = 1,
	PileDamageUp = 2,
	BowDamageUp = 3,
	HolyDamageUp = 4,
	WaterHpUp = 5,
	PileHpUp = 6,
	BowHpUp = 7,
	HolyHpUp = 8,
	WaterSpeedUp = 9,
	PileSpeedUp = 10,
	BowSpeedUp = 11,
	HolySpeedUp = 12,
	Garlic = 13,
	Bible = 14,
	SilverRing = 15,
	laurel = 16,
	Wine = 17,
	Mirror = 18,
};

#define artifact Artifact::GetInstance().get()

class Artifact : public SingletonBase<Artifact>
{
	struct  artifactPower
	{
		int atkLevel = 1;
		int spdLevel = 1;
		int hpLevel = 1;
	};
public:
	artifactPower WaterPower;
	artifactPower BowPower;
	artifactPower HolyPower;
	artifactPower PilePower;

	ArtifactData artifactData;

	// 스탯 증가를 한번만 하기위한 변수
	bool isUpdate = false;

	Artifact();
	virtual ~Artifact();
	void PowerUP(int level, TowerBase* tower);
	void RangeUp(TowerBase* tower);
	void knockbackUp(TowerBase* tower);

	bool isOwned(int id);
	int checkLevel(int id);
	void SelectArtifact(int id);
	void SelectArtifact(ArtifactId id);

	std::vector<int> ownedArtifact;

};

