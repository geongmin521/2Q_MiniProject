#pragma once
#include "SingletonBase.h"

class Button;
class GameManager :public SingletonBase<GameManager>
{
private:

public:
	bool isBattle;
	int WaveLevel = 1;
	int curWaveId = 1000;
	int LiveEenmy = 0; //���������������� 

	std::function<void(void)> ShowWave;
	std::function<void(void)> EndWave;
	std::function<void(void)> GameClear;
	GameManager();
	~GameManager(); //���� �Ŵ���.. 
	void Update();
};

#define gameManager GameManager::GetInstance().get()