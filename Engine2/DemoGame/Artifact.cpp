#include "pch.h"
#include "Artifact.h"
#include "GameObject.h"

Artifact::Artifact()
{
	//DataManager::GetInstance().get()->CSVReader(L"ArtifactData");
}

Artifact::~Artifact()

{
}

void Artifact::PowerUP(int id)
{
	// csv나오면 구성
	switch (id)
	{
	case 1:
		WaterPower.Attack += 2;
		//ownedArtifact.push_back(ArtifactId::WaterDamageUp);
		break;
	case 2:
		PilePower.Attack += 2;
		//ownedArtifact.push_back(ArtifactId::PileDamageUp);
		break;
	case 3:
		BowPower.Attack += 2;
		//ownedArtifact.push_back(ArtifactId::BowDamageUp);
		break;
	case 4:
		HolyPower.Attack += 2;
		//ownedArtifact.push_back(ArtifactId::HolyDamageUp);
		break;
	case 5:
		WaterPower.Hp += 50;
		//ownedArtifact.push_back(ArtifactId::WaterHpUp);
		break;
	case 6:
		PilePower.Hp += 50;
		//ownedArtifact.push_back(ArtifactId::PileHpUp);
		break;
	case 7:
		BowPower.Hp += 50;
		//ownedArtifact.push_back(ArtifactId::BowHpUp);
		break;
	case 8:
		HolyPower.Hp += 50;
		//ownedArtifact.push_back(ArtifactId::HolyHpUp);
		break;
	case 9:
		WaterPower.attackSpeed += 0.2f;
		//ownedArtifact.push_back(ArtifactId::WaterSpeedUp);
		break;
	case 10:
		PilePower.attackSpeed += 0.2f;
		//ownedArtifact.push_back(ArtifactId::PileSpeedUp);
		break;
	case 11:
		BowPower.attackSpeed += 0.2f;
		//ownedArtifact.push_back(ArtifactId::BowSpeedUp);
		break;
	case 12:
		HolyPower.attackSpeed += 0.2f;
		//ownedArtifact.push_back(ArtifactId::HolySpeedUp);
		break;
	case 13:
		//ownedArtifact.push_back(ArtifactId::Garlic);
		break;
	case 14:
		//ownedArtifact.push_back(ArtifactId::Bible);
		break;
	case 15:
		//ownedArtifact.push_back(ArtifactId::SilverRing);
		break;
	case 16:
		//ownedArtifact.push_back(ArtifactId::laurel);
		break;
	case 17:
		//ownedArtifact.push_back(ArtifactId::Wine);
		break;
	case 18:
		//ownedArtifact.push_back(ArtifactId::Mirror);
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



