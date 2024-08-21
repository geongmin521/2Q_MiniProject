#pragma once
#include "SingletonBase.h"
#include "Data.h"

class Image;
class TowerBase;
enum class ArtifactId
{
	WaterDamageUp = 500,
	PileDamageUp = 501,
	BowDamageUp = 502,
	HolyDamageUp = 503,
	WaterHpUp = 504,
	PileHpUp = 505,
	BowHpUp = 506,
	HolyHpUp = 507,
	WaterSpeedUp = 508,
	PileSpeedUp = 509,
	BowSpeedUp = 510,
	HolySpeedUp = 511,
	Garlic = 512,
	Bible = 513,
	SilverRing = 514,
	Laurel = 515,
	Wine = 516,
	Mirror = 517,
};

#define artifact Artifact::GetInstance().get()

class Artifact : public SingletonBase<Artifact>
{
	struct  artifactPower
	{
		int atkLevel = 0;
		int spdLevel = 0;
		int hpLevel = 0;

		void increaseAtk() { atkLevel++; }
		void increaseHp() { hpLevel++; }
		void increaseSpd() { spdLevel++; }
	};
public:
	artifactPower WaterPower;
	artifactPower CrossbowPower;
	artifactPower HolyPower;
	artifactPower PilePower;

	std::unordered_map<int, std::function<void()>> levelUpActions;

	Artifact();
	virtual ~Artifact();
	void Init();
	void levelUp(int id);
	bool isOwned(int id);
	void SelectArtifact(int id);

	void ResetStat(artifactPower power);

	std::vector<int> ownedArtifact;

};

