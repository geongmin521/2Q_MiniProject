#pragma once
#include "SingletonBase.h"
class GameManager :public SingletonBase<GameManager>
{
private:
	bool isBattle;
public:
	GameManager();
	~GameManager(); //게임 매니저.. 

};

