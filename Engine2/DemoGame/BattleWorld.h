#pragma once
#include "World.h"

class Shop;
class ShowWave;
class Combination;
class Container;
class BattleWorld : public World
{
private:
	Shop* shop;         //상점 UI
	ShowWave* showWave; //적 웨이브 UI
	Combination* combination; //조합표UI
	std::vector<Container*> IconInven;// 인벤토리

public:
	BattleWorld(); 
	virtual ~BattleWorld();
	void MakeObject() override;
	void MakeUI();
};

