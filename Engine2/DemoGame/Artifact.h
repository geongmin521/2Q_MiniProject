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
	// ui ��Ƽ��Ʈ�� ������ �׷��� ownarti�� �� ��� ������Ʈ���� �긦 �������־� �갡 ��ȣ�� ���ݾ� init�Ҷ� ��� �߰����� ���Ѵ�
    // ��� ������Ʈ���� init�Ҷ� ���̵�˻��ؾ��� ���ʹ̾�Ƽ��Ʈ Ÿ����Ƽ��Ʈ ui��Ƽ��Ʈ  
};

