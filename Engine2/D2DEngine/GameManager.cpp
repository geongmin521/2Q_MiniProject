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
	if (LiveEenmy == 0&& isBattle ==true)//������ ������̰� ���� ���̺갡��
	{
	
		if (WaveLevel == 8)
		{
			GameClear();
			//����Ŭ����//�� ���� �Ŵ������� ���ٽ����� ����ְ��ؾ��ϳ�? 
			return;
		}
		else
		{
			WaveLevel++;
		}
		DataManager::GetInstance().get()->ChoseWave(); //������� �ȉ��.. 	
		isBattle = false;
		EndWave(); //������ư Ȱ��ȭ�ϱ�
	}
		
}
