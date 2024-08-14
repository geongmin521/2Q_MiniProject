#pragma once
#include "UI.h"

class Image;
class Container;
class Combination;
class D2DFont;
class EnemySpawner;
class Shop: public UI 
{
private:
	bool isLock[5];
	int Id[5]; 
	int reroll = 10;
	std::vector<Image*> Icons;				
	std::vector<std::wstring> ImagePath;	
	std::vector<std::wstring> TowerName;	
	std::vector<int> compensationList; 
	std::wstring Text;
	std::vector<Container*> Containers; 
	Combination* combination;
	D2DFont* compensationText;
	D2DFont* rerollText;
	D2DFont* rerollButtonText;

public:
	EnemySpawner* spawner;
	Shop();
	void init();
	virtual ~Shop();
	void Reroll();
	void Spawn(); 
	void MakeText(int order,int count);
	void SetOtherUI(std::vector<Container*> container, Combination* combination) { this->Containers = container; this->combination = combination;}
	int TowerNameToID(std::wstring name); 

};

