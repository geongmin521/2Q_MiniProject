#pragma once
#include "../D2DEngine/SingletonBase.h"
#include "../D2DEngine/DataManager.h"

class GameObject;

enum class ArtifactId
{
	HealthUp = 1,
	EnemyHpDown = 2,
};

struct artifactPower
{
	float Attack = 1.f;
	float Armor = 1.f;
	float Speed = 1.f;
};

class Artifact : public SingletonBase<Artifact>
{
public:
	artifactPower towerPower;
	artifactPower enemyPower;

	ArtifactData artifactData;

	Artifact();
	virtual ~Artifact();

	void AttackUP() { towerPower.Attack += 0.3f; }
	void ArmorUP() { towerPower.Armor += 0.3f; }
	void SpeedUP() { towerPower.Speed += 0.3f; }

	std::vector<ArtifactId> ownArtifact;
	// ui 아티팩트를 선택해 그러면 ownarti에 들어가 모든 오브젝트에서 얘를 받을수있어 얘가 번호가 있잖아 init할때 모든 추가값을 더한다
    // 모든 오브젝트에서 init할때 아이디검색해야함 에너미아티팩트 타워아티팩트 ui아티팩트  
};

