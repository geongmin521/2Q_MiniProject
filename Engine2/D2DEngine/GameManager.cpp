#include "pch.h"
#include "GameManager.h"
#include "DataManager.h"
#include "D2DEffectManager.h"
#include "CrossFadeEffect.h"
#include "../DemoGame/Artifact.h"

GameManager::GameManager()
{
	
}

GameManager::~GameManager()
{
}

void GameManager::Update()
{

	if (LiveEenmy == 0&& isBattle ==true)//웨이브 클리어
	{
		if (WaveLevel == 8)
		{
			events[Event::GameOverEvent]();
			return;
		}
		else
		{			
			WaveLevel++;
			if (artifact->isOwned(static_cast<int>(ArtifactId::Bible)))
			{
				gold += goldReward[WaveLevel] + goldReward[WaveLevel] * 0.3f;
			}
			gold += goldReward[WaveLevel];
		}
		dataManager->ChoseWave();
		D2DEffectManager::GetInstance()->FindIEffect<CrossFadeEffect>(L"MapFade")->isFadeIn = true;
		isBattle = false;
		events[Event::EndWave]();
	}		
}

void GameManager::reset()
{
	isBattle = false;
	WaveLevel = 1;
	curWaveId = 1000;
	LiveEenmy = 0;
	gold = 0;
	chance = 1;
}
