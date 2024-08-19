#include "pch.h"
#include "GameManager.h"
#include "DataManager.h"

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
		}
		dataManager->ChoseWave();
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
	gold = 100;
	chance = 1;
}
