#pragma once
#include "World.h"

class Shop;
class ShowWave;
class Combination;
class EnemySpawner;
class Container;
class BattleWorld : public World
{
private:
	Shop* shop;         //���� UI
	ShowWave* showWave; //�� ���̺� UI
	Combination* combination; //����ǥUI
	EnemySpawner* spwaner;
	std::vector<Container*> IconInven;// �κ��丮

public:
	
	BattleWorld(); 
	virtual ~BattleWorld();
	void MakeObject() override;
	void MakeUI();
};

