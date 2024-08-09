#pragma once
#include "../D2DEngine/SingletonBase.h"
#include "../D2DEngine/DataManager.h"

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
	artifactPower towerPower;
	artifactPower enemyPower;

	ArtifactData artifactData;

	Artifact();
	virtual ~Artifact();
	void AttackUP() { towerPower.Attack += 0.3f; }
	void ArmorUP() { towerPower.Armor += 0.3f; }
	void HpUP() { towerPower.Hp += 0.3f; }
	std::vector<ArtifactId> ownArtifact;
	// ui ��Ƽ��Ʈ�� ������ �׷��� ownarti�� �� ��� ������Ʈ���� �긦 �������־� �갡 ��ȣ�� ���ݾ� init�Ҷ� ��� �߰����� ���Ѵ�
    // ��� ������Ʈ���� init�Ҷ� ���̵�˻��ؾ��� ���ʹ̾�Ƽ��Ʈ Ÿ����Ƽ��Ʈ ui��Ƽ��Ʈ  
};

