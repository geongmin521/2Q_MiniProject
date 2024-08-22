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
class GameManager :public SingletonBase<GameManager>//싱글톤에 리셋을 부여하던가 아니면 데이터는 싱글톤이 아니고 관리만 싱글톤으로 하는것도 방법이긴하네.. 
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
	std::vector<std::function<void(void)>> Reset;//원래 다 이렇게했어야했는데 시간이 없으니 이거하나만 빼놓자.  

	GameManager();
	~GameManager(); 
	void Update();
	virtual void reset() override;
	void ResetFunc();
	int GetGold() { return gold; };
	void UseGold(int use) { gold -= use; events[Event::UseGold](); }; 
};

