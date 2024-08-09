#pragma once
#include "SingletonBase.h"



class GameManager :public SingletonBase<GameManager>
{
private:

public:
	bool isBattle;
	int WaveLevel = 1;
	GameManager();
	~GameManager(); //게임 매니저.. 

};

#define gameManager GameManager::GetInstance().get()