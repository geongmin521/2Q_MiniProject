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
	// ui ��Ƽ��Ʈ�� ������ �׷��� ownarti�� �� ��� ������Ʈ���� �긦 �������־� �갡 ��ȣ�� ���ݾ� init�Ҷ� ��� �߰����� ���Ѵ�
    // ��� ������Ʈ���� init�Ҷ� ���̵�˻��ؾ��� ���ʹ̾�Ƽ��Ʈ Ÿ����Ƽ��Ʈ ui��Ƽ��Ʈ  
};

