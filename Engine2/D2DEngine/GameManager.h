#pragma once
#include "SingletonBase.h"
class GameManager :public SingletonBase<GameManager>
{
private:
	bool isBattle;
public:
	GameManager();
	~GameManager(); //���� �Ŵ���.. 

};

