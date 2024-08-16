#pragma once
#include "World.h"

class Shop;
class D2DFont; 
class ShowWave;
class ShowWave;
class GameObject;
class BattleWorld : public World
{
private:
	Shop* shop;					//상점 UI
	D2DFont* WaveCount;			//웨이브카운트
	D2DFont* goldText;				//재화텍스트
	ShowWave* showWave;			//적 웨이브 UI
	std::map<std::string, GameObject*> Objs;//따로관리하는 오브젝트
public:

	BattleWorld(); 
	virtual ~BattleWorld();
	void MakeObject() override;
	void MakeUI();
	void RegisterEvent();
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget, float Alpha = 1);
};

