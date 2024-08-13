#pragma once
#include "World.h"

class Shop;
class ShowWave;
class Combination;
class EnemySpawner;
class Container;
class Button;
class Image;
class BattleWorld : public World
{
private:
	Shop* shop;         //상점 UI
	ShowWave* showWave; //적 웨이브 UI
	Combination* combination; //조합표UI
	EnemySpawner* spwaner;
	Image* WaveCount;
	std::vector<Container*> TowerInventory;
	bool Swap = false;
public:
	Button* shop_spawnButton;
	BattleWorld(); 
	virtual ~BattleWorld();
	void MakeObject() override;
	void MakeUI();
	void ChangeButton();
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget, float Alpha = 1);
};

