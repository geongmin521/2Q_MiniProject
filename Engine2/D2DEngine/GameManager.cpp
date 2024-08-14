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
			GameClear();
			return;
		}
		else
		{
			WaveLevel++;
		}
		DataManager::GetInstance().get()->ChoseWave();
		isBattle = false;
		EndWave(); 
	}
		
}
