#include "pch.h"
#include "Artifact.h"
#include "Factory.h"
#include "Image.h"
#include "TowerBase.h"

Artifact::Artifact()
{
	//dataManager->CSVReader(L"ArtifactData");
	// csv ���� �� ������ ������
}

Artifact::~Artifact()

{
}

void Artifact::SelectArtifact(int id)
{
	ownedArtifact.push_back(id);
	levelUp(id);
	//��Ƽ��Ʈ csv�̸��̶� �̹��� �̸� ��ġ��Ű��
	Make(Image)(L"Crossbow.png").setPosition({ 100.f * ownedArtifact.size() ,100 });
}
// ������ ���� �ö󰡾����� �𸣰ھ ���� �� ����

void Artifact::RangeUp(TowerBase* tower)
{
	if (tower->towerData.Type == "Crossbow")
	{
		if (tower->towerData.level == 1)
		{
			tower->towerData.attackRange = 700.0f;
		}
		else if (tower->towerData.level == 2)
		{
			tower->towerData.attackRange = 800.0f;
		}
		else if (tower->towerData.level == 3)
		{
			tower->towerData.attackRange = 800.0f;
		}
		
	}
	else if (tower->towerData.Type == "Water")
	{
		if (tower->towerData.level == 1)
		{
			tower->towerData.attackRange = 600.0f;
		}
		else if (tower->towerData.level == 2)
		{
			tower->towerData.attackRange = 600.0f;
		}
		else if (tower->towerData.level == 3)
		{
			tower->towerData.attackRange = 700.0f;
		}
	}
	else if (tower->towerData.Type == "Pile")
	{
		if (tower->towerData.level == 1)
		{
			tower->towerData.attackRange = 200.0f;
		}
		else if (tower->towerData.level == 2)
		{
			tower->towerData.attackRange = 200.0f;
		}
		else if (tower->towerData.level == 3)
		{
			tower->towerData.attackRange = 200.0f;
		}
	}
	else if (tower->towerData.Type == "HolyCross")
	{
		if (tower->towerData.level == 1)
		{
			tower->towerData.attackRange = 275.0f;
		}
		else if (tower->towerData.level == 2)
		{
			tower->towerData.attackRange = 275.0f;
		}
		else if (tower->towerData.level == 3)
		{
			tower->towerData.attackRange = 350.0f;
		}
	}
	else if (tower->towerData.Type == "Hidden")
	{
		tower->towerData.attackRange = 1300.0f;
	}
}

void Artifact::knockbackUp(TowerBase* tower)
{
	if (tower->towerData.Type == "Crossbow")
	{
		tower->towerData.knockBack = 40.f;
	}
	else if (tower->towerData.Type == "Water")
	{
		tower->towerData.knockBack = 65.f;
	}
	else if (tower->towerData.Type == "Pile")
	{
		tower->towerData.knockBack = 15.f;
	}
	else if (tower->towerData.Type == "Hidden")
	{
		tower->towerData.knockBack = 30.f;
	}
}

void Artifact::levelUp(int id)
{
	switch (id)
	{
	case 1:
		WaterPower.atkLevel++;
		break;
	case 2:
		PilePower.atkLevel++;
		break;
	case  3:
		BowPower.atkLevel++;
		break;
	case 4:
		HolyPower.atkLevel++;
		break;
	case 5:
		WaterPower.hpLevel++;
		break;
	case 6:
		PilePower.hpLevel++;
		break;
	case 7:
		BowPower.hpLevel++;
		break;
	case 8:
		HolyPower.hpLevel++;
		break;
	case 9:
		WaterPower.spdLevel++;
		break;
	case 10:
		PilePower.spdLevel++;
		break;
	case 11:
		BowPower.spdLevel++;
		break;
	case 12:
		HolyPower.spdLevel++;
		break;
	}
}

bool Artifact::isOwned(int id)
{
	std::vector<int>::iterator it;
	it = std::find(ownedArtifact.begin(), ownedArtifact.end(), id);
	if (it != ownedArtifact.end())
	{
		return true;
	}
	return false;
}



