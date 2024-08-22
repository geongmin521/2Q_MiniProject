#pragma once
#include "SingletonBase.h"

enum Event
{
	GameOverEvent,  
	EndWave,
	SpawnEnemy,
	ShowWaveFunc,
	UseGold,
	OpenCombination,
	OpenGodStore,
	GameClearEvent,
	//Reset
};

#define gameManager GameManager::GetInstance().get()

class Button;
class GameObject;
class GameManager :public SingletonBase<GameManager>//�̱��濡 ������ �ο��ϴ��� �ƴϸ� �����ʹ� �̱����� �ƴϰ� ������ �̱������� �ϴ°͵� ����̱��ϳ�.. 
{
private:
	int gold = 0;
public:
	bool isBattle;
	int WaveLevel = 1;
	int curWaveId = 1000;
	int LiveEenmy = 0; 
	int chance = 1; 
	int goldReward[7] = { 12,14,18,18,20,24,26 };
	std::map<Event, std::function<void(void)>> events; 
	std::function<GameObject*(std::string key)> getObject; 
	std::function<void(bool)> Compensation; 
	std::vector<std::function<void(void)>> Reset;//���� �� �̷����߾���ߴµ� �ð��� ������ �̰��ϳ��� ������.  

	GameManager();
	~GameManager(); 
	void Update();
	virtual void reset() override;
	void ResetFunc();
	int GetGold() { return gold; };
	void UseGold(int use) { gold -= use; events[Event::UseGold](); }; 
};

