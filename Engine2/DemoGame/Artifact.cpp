#include "pch.h"
#include "Artifact.h"
#include "Factory.h"
#include "Image.h"

Artifact::Artifact()
{
	//dataManager->CSVReader(L"ArtifactData");
}

Artifact::~Artifact()

{
}

void Artifact::SelectAtrifact(int id)
{
	ownedArtifact.push_back(id);
	//아티팩트 csv이름이랑 이미지 이름 일치시키기
	Make(Image)(L"Crossbow.png").setPosition({ 100.f * ownedArtifact.size() ,100});
}

void Artifact::PowerUP(int id)
{
	// csv나오면 구성
	// 일단은 스탯과 vector를 분리
	switch (id)
	{
	case 1:
		WaterPower.Attack += 2;
		ownedArtifact.push_back(static_cast<int>(ArtifactId::WaterDamageUp));
		break;
	case 2:
		PilePower.Attack += 2;
		ownedArtifact.push_back(static_cast<int>(ArtifactId::PileDamageUp));
		break;
	case 3:
		BowPower.Attack += 2;
		ownedArtifact.push_back(static_cast<int>(ArtifactId::BowDamageUp));
		break;
	case 4:
		HolyPower.Attack += 2;
		ownedArtifact.push_back(static_cast<int>(ArtifactId::HolyDamageUp));
		break;
	case 5:
		WaterPower.Hp += 50;
		ownedArtifact.push_back(static_cast<int>(ArtifactId::WaterHpUp));
		break;
	case 6:
		PilePower.Hp += 50;
		ownedArtifact.push_back(static_cast<int>(ArtifactId::PileHpUp));
		break;
	case 7:
		BowPower.Hp += 50;
		ownedArtifact.push_back(static_cast<int>(ArtifactId::BowHpUp));
		break;
	case 8:
		HolyPower.Hp += 50;
		ownedArtifact.push_back(static_cast<int>(ArtifactId::HolyHpUp));
		break;
	case 9:
		WaterPower.attackSpeed += 0.2f;
		ownedArtifact.push_back(static_cast<int>(ArtifactId::WaterSpeedUp));
		break;
	case 10:
		PilePower.attackSpeed += 0.2f;
		ownedArtifact.push_back(static_cast<int>(ArtifactId::PileSpeedUp));
		break;
	case 11:
		BowPower.attackSpeed += 0.2f;
		ownedArtifact.push_back(static_cast<int>(ArtifactId::BowSpeedUp));
		break;
	case 12:
		HolyPower.attackSpeed += 0.2f;
		ownedArtifact.push_back(static_cast<int>(ArtifactId::HolySpeedUp));
		break;
	case 13:
		ownedArtifact.push_back(static_cast<int>(ArtifactId::Garlic));
		break;
	case 14:
		// 재화가 어떻게 구성되어있는지 몰라서 후 구현
		ownedArtifact.push_back(static_cast<int>(ArtifactId::Bible));
		break;
	case 15:
		ownedArtifact.push_back(static_cast<int>(ArtifactId::SilverRing));
		break;
	case 16:
		ownedArtifact.push_back(static_cast<int>(ArtifactId::laurel));
		break;
	case 17:
		ownedArtifact.push_back(static_cast<int>(ArtifactId::Wine));
		break;
	case 18:
		ownedArtifact.push_back(static_cast<int>(ArtifactId::Mirror));
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



