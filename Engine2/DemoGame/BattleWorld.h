#pragma once
#include "../D2DEngine/World.h"
class Shop;
class ShowWave;
class Combination;
class BattleWorld : public World
{
private:
	Shop* shop;         //상점 UI
	ShowWave* showWave; //적 웨이브 UI
	Combination* combination; //조합표UI
public:
	BattleWorld(); 
	~BattleWorld();
	void MakeObject() override;
	void MakeUI();
};

