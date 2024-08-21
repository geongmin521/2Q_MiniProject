#include "pch.h"
#include "CommonFunc.h"
#include "CircleCollider.h"
#include "GameObject.h"
#include "circle.h"
#include "Transform.h"
#include "Artifact.h"
#include "DataManager.h"

void CommonFunc::FindTarget(CircleCollider& myCol, std::string tag, std::vector<GameObject*>& target, float Range) //단일 타겟 검색
{
	target.clear();
	GameObject* enemy = nullptr;
	int minDistance = INT_MAX;
	if (myCol.owner->name == "Tower" && artifact->isOwned(static_cast<int>(ArtifactId::SilverRing)))
	{
		ArtifactData art = dataManager->getArtifactData(static_cast<int>(ArtifactId::SilverRing));
		Range += art.power;
	}
	for (auto& tragetCol : myCol.collideStatePrev)
	{
		if (tragetCol->owner->name == tag && tragetCol->owner->GetActive() == true)
		{
			
			float distance = myCol.circle->GetDistance(tragetCol->owner->transform->GetWorldLocation());
			if (distance < minDistance && distance < Range)
			{
				minDistance = distance;
				enemy = tragetCol->owner;
			}
		}
	}
	if (enemy != nullptr)
		target.push_back(enemy);
}

void CommonFunc::FindTargets(CircleCollider& myCol, std::string tag, std::vector<GameObject*>& targets, float Range) //여러 타겟 검사하기
{
	targets.clear();
	if (myCol.owner->name == "Tower" && artifact->isOwned(static_cast<int>(ArtifactId::SilverRing)))
	{
		ArtifactData art = dataManager->getArtifactData(static_cast<int>(ArtifactId::SilverRing));
		Range += art.power;
	}
	for (auto& tragetCol : myCol.collideStatePrev) 
	{
		if (tragetCol->owner->name == tag && tragetCol->owner->GetActive() == true)
		{

			float distance = (myCol.owner->GetWorldLocation() - tragetCol->owner->GetWorldLocation()).Length();
			if (distance > Range)
				continue;
			targets.push_back(tragetCol->owner);
		}
	}
}