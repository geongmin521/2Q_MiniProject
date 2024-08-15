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
	int LiveEenmy = 0; 
	int gold = 100;
	std::map<std::string, std::function<void(void)>> events; //이벤트매니저는따로 만들지않음
	GameManager();
	~GameManager(); 
	void Update();
	void init();
};

#define gameManager GameManager::GetInstance().get()