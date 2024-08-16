#pragma once
#include "SingletonBase.h"

enum Event
{
	GameOverEvent,  
	EndWave,
	SpawnEnemy,
	UseGold,
	Reset
};

#define gameManager GameManager::GetInstance().get()

class Button;
class GameManager :public SingletonBase<GameManager>//싱글톤에 리셋을 부여하던가 아니면 데이터는 싱글톤이 아니고 관리만 싱글톤으로 하는것도 방법이긴하네.. 
{
private:
	int gold = 100;
public:
	bool isBattle;
	int WaveLevel = 1;
	int curWaveId = 1000;
	int LiveEenmy = 0; 
	int chance = 1; 
	std::map<Event, std::function<void(void)>> events; 
	GameManager();
	~GameManager(); 
	void Update();
	void reset();
	int GetGold() { return gold; };
	void UseGold(int use) { gold -= use; events[Event::UseGold](); }; 
};

