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
class GameManager :public SingletonBase<GameManager>//�̱��濡 ������ �ο��ϴ��� �ƴϸ� �����ʹ� �̱����� �ƴϰ� ������ �̱������� �ϴ°͵� ����̱��ϳ�.. 
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

