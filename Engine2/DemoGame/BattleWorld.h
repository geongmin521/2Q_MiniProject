#pragma once
#include "World.h"

class Shop;
class D2DFont; 
class ShowWave;
class GameObject;
class Button;
class BattleWorld : public World
{
private:
	Shop* shop;					//상점 UI
	D2DFont* goldText;			//재화텍스트
	ShowWave* showWave;			//적 웨이브 UI
	Button* TimeScaleButton[3];
	std::map<std::string, GameObject*> Objs; //따로관리하는 오브젝트

	D2DFont* BossDialogue;			// 보스 대사
public:

	BattleWorld(); 
	virtual ~BattleWorld();
	void MakeObject() override;
	void MakeUI();
	void RegisterEvent();
	void TimeScaleIsClick(int num);
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget, float Alpha = 1);
};

