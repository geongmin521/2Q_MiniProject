#pragma once
#include "World.h"

class Shop;
class ShowWave;
class Combination;
class EnemySpawner;
class Container;
class Button;
class BattleWorld : public World
{
private:
	Shop* shop;         //상점 UI
	ShowWave* showWave; //적 웨이브 UI
	Combination* combination; //조합표UI
	EnemySpawner* spwaner;
	std::vector<Container*> IconInven;
	Button* shopButton;
	Button* spawnButton;

public:
	
	BattleWorld(); 
	virtual ~BattleWorld();
	void MakeObject() override;
	void MakeUI();
};

