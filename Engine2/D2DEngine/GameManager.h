#pragma once
#include "SingletonBase.h"



class GameManager :public SingletonBase<GameManager>
{
private:

public:
	bool isBattle; //이게 트루가되는시점에 소환하면되나? set을만들어서? 사실 내가 뭘해야할지도 모르겠네.. 
	int WaveLevel = 1;
	GameManager();
	~GameManager(); //게임 매니저.. 

};

#define gameManager GameManager::GetInstance().get()