#pragma once
#include "SingletonBase.h"
#include "Data.h"

class Image;
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
	Laurel = 16,
	Wine = 17,
	Mirror = 18,
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
	artifactPower BowPower;
	artifactPower HolyPower;
	artifactPower PilePower;

	ArtifactData artifactData;

	float knockback = 0.f;
	float Range = 0.f;

	Image* m_Image;

	std::unordered_map<int, std::function<void()>> levelUpActions;

	Artifact();
	virtual ~Artifact();
	void Init();
	void levelUp(int id);
	bool isOwned(int id);
	void SelectArtifact(int id);
	int bibleGold(int gold);
	std::vector<int> ownedArtifact;

};

