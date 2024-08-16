#pragma once
#include "SingletonBase.h"
#include "DataManager.h"

class GameObject;

enum class ArtifactId
{
	HealthUp = 1,
	EnemyHpDown = 2,
	MeleeDamageUp = 3,
	RangedDamageUp = 4,
};



class Artifact : public SingletonBase<Artifact>
{
	struct  artifactPower
	{
		float Attack = 1;
		float Armor = 1;
		float Hp = 1;
	};
public:
	artifactPower CrossbowPower;
	artifactPower HolyCrossPower;
	artifactPower PilePower;

	ArtifactData artifactData;

	Artifact();
	virtual ~Artifact();
	void AttackUP(int id);
	void AttackSpeedUp(int id);
	void HpUP(int id);

	std::vector<ArtifactId> ownArtifact;
	// ui ��Ƽ��Ʈ�� ������ �׷��� ownarti�� �� ��� ������Ʈ���� �긦 �������־� �갡 ��ȣ�� ���ݾ� init�Ҷ� ��� �߰����� ���Ѵ�
    // ��� ������Ʈ���� init�Ҷ� ���̵�˻��ؾ��� ���ʹ̾�Ƽ��Ʈ Ÿ����Ƽ��Ʈ ui��Ƽ��Ʈ  
};

