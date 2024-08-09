#pragma once
#include "World.h"

class Shop;
class ShowWave;
class Combination;
class Container;
class BattleWorld : public World
{
private:
	Shop* shop;         //���� UI
	ShowWave* showWave; //�� ���̺� UI
	Combination* combination; //����ǥUI
	std::vector<Container*> IconInven;// �κ��丮

public:
	BattleWorld(); 
	virtual ~BattleWorld();
	void MakeObject() override;
	void MakeUI();
};

