#include "pch.h"
#include "GameManager.h"
#include "DataManager.h"
#include "D2DEffectManager.h"
#include "CrossFadeEffect.h"
#include "../DemoGame/Artifact.h"

GameManager::GameManager()
{
	this->Reset.push_back([this]() { reset(); });
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
			else
			{
				gold += goldReward[WaveLevel];
			}
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
	if (events[Event::ShowWaveFunc] != nullptr)
		events[Event::ShowWaveFunc] = nullptr; //다시시작할때 터져서 일단 이렇게 처리함
}

void GameManager::ResetFunc()
{
	for (auto val : Reset)
		val();
}
