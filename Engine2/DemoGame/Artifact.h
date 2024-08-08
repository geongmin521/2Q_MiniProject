#pragma once
#include "../D2DEngine/SingletonBase.h"
#include "../D2DEngine/DataManager.h"

class GameObject;

enum class ArtifactId
{
	HealthUp = 1,
	EnemyHpDown = 2,
};

struct  artifactPower
{
	float AttackUp =1;
};

class Artifact : public SingletonBase<Artifact>
{
public:
	artifactPower power;
	Artifact();
	virtual ~Artifact();
	ArtifactData artifactData;
	void AttackUP() { power.AttackUp += 0.3f; }
	std::vector<ArtifactId> ownArtifact;
	// ui 아티팩트를 선택해 그러면 ownarti에 들어가 모든 오브젝트에서 얘를 받을수있어 얘가 번호가 있잖아 init할때 모든 추가값을 더한다
    // 모든 오브젝트에서 init할때 아이디검색해야함 에너미아티팩트 타워아티팩트 ui아티팩트  
};

