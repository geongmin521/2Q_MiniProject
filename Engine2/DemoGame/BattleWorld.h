#pragma once
#include "../D2DEngine/World.h"
class Shop;
class ShowWave;
class Combination;
class BattleWorld : public World
{
private:
	Shop* shop;         //���� UI
	ShowWave* showWave; //�� ���̺� UI
	Combination* combination; //����ǥUI
public:
	BattleWorld(); 
	~BattleWorld();
	void MakeObject() override;
	void MakeUI();
};

