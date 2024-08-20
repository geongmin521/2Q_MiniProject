#include "pch.h"
#include "Artifact.h"
#include "Factory.h"
#include "Image.h"
#include "TowerBase.h"

Artifact::Artifact()
{
	//dataManager->CSVReader(L"ArtifactData");
}

Artifact::~Artifact()

{
}

void Artifact::SelectArtifact(int id)
{
	ownedArtifact.push_back(id);
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
	//아티팩트 csv이름이랑 이미지 이름 일치시키기
	Make(Image)(L"Crossbow.png").setPosition({ 100.f * ownedArtifact.size() ,100 });
}

void Artifact::SelectArtifact(ArtifactId id)
{
	ownedArtifact.push_back(static_cast<int>(id));
}

void Artifact::PowerUP(int level, TowerBase* tower)
{
	// csv나오면 구성
	// 일단은 스탯과 vector를 분리
	if (level == 1)
	{
		if (tower->towerData.Type == "Crossbow")
		{
			if (artifact->BowPower.hpLevel == 2)
			{
				tower->towerData.HP = 40;
			}
			else if (artifact->BowPower.hpLevel == 3)
			{
				tower->towerData.HP = 60;
			}
			if (artifact->BowPower.spdLevel == 2)
			{
				tower->towerData.attackSpeed = 0.8f;
			}
			else if (artifact->BowPower.spdLevel == 3)
			{
				tower->towerData.attackSpeed = 0.6f;
			}
		}
		else if (tower->towerData.Type == "Water")
		{
			if (artifact->WaterPower.hpLevel == 2)
			{
				tower->towerData.HP = 40;
			}
			else if (artifact->WaterPower.hpLevel == 3)
			{
				tower->towerData.HP = 60;
			}
			if (artifact->WaterPower.spdLevel == 2)
			{
				tower->towerData.attackSpeed = 1.3f;
			}
			else if (artifact->WaterPower.spdLevel == 3)
			{
				tower->towerData.attackSpeed = 1.1f;
			}
		}
		else if (tower->towerData.Type == "Pile")
		{
			if (artifact->PilePower.hpLevel == 2)
			{
				tower->towerData.HP = 70;
			}
			else if (artifact->PilePower.hpLevel == 3)
			{
				tower->towerData.HP = 90;
			}
			if (artifact->PilePower.spdLevel == 2)
			{
				tower->towerData.attackSpeed = 0.8f;
			}
			else if (artifact->PilePower.spdLevel == 3)
			{
				tower->towerData.attackSpeed = 0.6f;
			}
		}
		else if (tower->towerData.Type == "HolyCross")
		{
			if (artifact->HolyPower.hpLevel == 2)
			{
				tower->towerData.HP = 50;
			}
			else if (artifact->HolyPower.hpLevel == 3)
			{
				tower->towerData.HP = 70;
			}
			if (artifact->HolyPower.spdLevel == 2)
			{
				tower->towerData.attackSpeed = 0.8f;
			}
			else if (artifact->HolyPower.spdLevel == 3)
			{
				tower->towerData.attackSpeed = 0.6f;
			}
		}
	}
	else if (level == 2)
	{
		if (tower->towerData.Type == "Crossbow")
		{
			if (artifact->BowPower.hpLevel == 2)
			{
				tower->towerData.HP = 70;
			}
			else if (artifact->BowPower.hpLevel == 3)
			{
				tower->towerData.HP = 90;
			}
			if (artifact->BowPower.spdLevel == 2)
			{
				tower->towerData.attackSpeed = 0.55f;
			}
			else if (artifact->BowPower.spdLevel == 3)
			{
				tower->towerData.attackSpeed = 0.35f;
			}
		}
		else if (tower->towerData.Type == "Water")
		{
			if (artifact->WaterPower.hpLevel == 2)
			{
				tower->towerData.HP = 70;
			}
			else if (artifact->WaterPower.hpLevel == 3)
			{
				tower->towerData.HP = 90;
			}
			if (artifact->WaterPower.spdLevel == 2)
			{
				tower->towerData.attackSpeed = 1.05f;
			}
			else if (artifact->WaterPower.spdLevel == 3)
			{
				tower->towerData.attackSpeed = 0.85f;
			}
		}
		else if (tower->towerData.Type == "Pile")
		{
			if (artifact->PilePower.hpLevel == 2)
			{
				tower->towerData.HP = 170;
			}
			else if (artifact->PilePower.hpLevel == 3)
			{
				tower->towerData.HP = 190;
			}
			if (artifact->PilePower.spdLevel == 2)
			{
				tower->towerData.attackSpeed = 0.8f;
			}
			else if (artifact->PilePower.spdLevel == 3)
			{
				tower->towerData.attackSpeed = 0.6f;
			}
		}
		else if (tower->towerData.Type == "HolyCross")
		{
			if (artifact->HolyPower.hpLevel == 2)
			{
				tower->towerData.HP = 95;
			}
			else if (artifact->HolyPower.hpLevel == 3)
			{
				tower->towerData.HP = 115;
			}
			if (artifact->HolyPower.spdLevel == 2)
			{
				tower->towerData.attackSpeed = 0.8f;
			}
			else if (artifact->HolyPower.spdLevel == 3)
			{
				tower->towerData.attackSpeed = 0.6f;
			}
		}
	}
	else if (level == 3)
	{
		if (tower->towerData.Type == "Crossbow")
		{
			if (artifact->BowPower.hpLevel == 2)
			{
				tower->towerData.HP = 120;
			}
			else if (artifact->BowPower.hpLevel == 3)
			{
				tower->towerData.HP = 140;
			}
			if (artifact->BowPower.spdLevel == 2)
			{
				tower->towerData.attackSpeed = 0.3f;
			}
			else if (artifact->BowPower.spdLevel == 3)
			{
				tower->towerData.attackSpeed = 0.1f;
			}
		}
		else if (tower->towerData.Type == "Water")
		{
			if (artifact->WaterPower.hpLevel == 2)
			{
				tower->towerData.HP = 120;
			}
			else if (artifact->WaterPower.hpLevel == 3)
			{
				tower->towerData.HP = 140;
			}
			if (artifact->WaterPower.spdLevel == 2)
			{
				tower->towerData.attackSpeed = 0.8f;
			}
			else if (artifact->WaterPower.spdLevel == 3)
			{
				tower->towerData.attackSpeed = 0.6f;
			}
		}
		else if (tower->towerData.Type == "Pile")
		{
			if (artifact->PilePower.hpLevel == 2)
			{
				tower->towerData.HP = 420;
			}
			else if (artifact->PilePower.hpLevel == 3)
			{
				tower->towerData.HP = 440;
			}
			if (artifact->PilePower.spdLevel == 2)
			{
				tower->towerData.attackSpeed = 0.8f;
			}
			else if (artifact->PilePower.spdLevel == 3)
			{
				tower->towerData.attackSpeed = 0.6f;
			}
		}
		else if (tower->towerData.Type == "HolyCross")
		{
			if (artifact->HolyPower.hpLevel == 2)
			{
				tower->towerData.HP = 170;
			}
			else if (artifact->HolyPower.hpLevel == 3)
			{
				tower->towerData.HP = 190;
			}
			if (artifact->HolyPower.spdLevel == 2)
			{
				tower->towerData.attackSpeed = 0.8f;
			}
			else if (artifact->HolyPower.spdLevel == 3)
			{
				tower->towerData.attackSpeed = 0.6f;
			}
		}
	}
}

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

int Artifact::checkLevel(int id)
{
	std::unordered_map<int, int> frequency;
	int cnt = 0;
	for (auto& num : ownedArtifact)
	{
		frequency[num]++;
	}
	for (auto& pair : frequency)
	{
		if (pair.second > 1)
		{
			cnt++;
		}
	}

	return cnt;
}


