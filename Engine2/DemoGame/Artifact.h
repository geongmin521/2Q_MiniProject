#pragma once
#include "SingletonBase.h"
#include "DataManager.h"

class GameObject;

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

class Artifact : public SingletonBase<Artifact>
{
	struct  artifactPower
	{
		float Attack = 0;
		float attackSpeed = 0;
		float Hp = 0;
	};
public:
	artifactPower WaterPower;
	artifactPower BowPower;
	artifactPower HolyPower;
	artifactPower PilePower;

	ArtifactData artifactData;

	Artifact();
	virtual ~Artifact();
	void PowerUP(int id);

	bool isOwned(int id);

	std::vector<int> ownedArtifact;
};

