#include "pch.h"
#include "GameManager.h"
#include "DataManager.h"

#include "D2DEffectManager.h"
#include "CrossFadeEffect.h"
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
		switch (WaveLevel) // 스테이지 별 보상 좀 보상이 규칙성있게 받는게 아니여서 코드 좀 더러움
		{
		case 1:
			gold += 12;
			break;
		case 2:
			gold += 14;
			break;
		case 3:
			gold += 18;
			break;
		case 4:
			gold += 18;
			break;
		case 5:
			gold += 20;
			break;
		case 6:
			gold += 24;
			break;
		case 7:
			gold += 26;
			break;
		default:
			break;
		}

		if (WaveLevel == 8)
		{
			events[Event::GameOverEvent]();
			return;
		}
		else
		{
			WaveLevel++;
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
