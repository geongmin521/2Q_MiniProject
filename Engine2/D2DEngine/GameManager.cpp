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
	if (LiveEenmy == 0&& isBattle ==true)//적들을 모두죽이고 다음 웨이브가됨
	{
	
		if (WaveLevel == 8)
		{
			GameClear();
			//게임클리어//또 게임 매니저한테 람다식으로 들고있게해야하나? 
			return;
		}
		else
		{
			WaveLevel++;
		}
		DataManager::GetInstance().get()->ChoseWave(); //보상아직 안됬고.. 	
		isBattle = false;
		EndWave(); //상점버튼 활성화하기
	}
		
}
