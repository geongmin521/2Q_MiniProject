#pragma once
#include "UI.h"

class Image;
class Container;
class D2DFont;
class Button;
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
	GameObject* combination;
	D2DFont* compensationText;
	D2DFont* rerollText;
	D2DFont* rerollButtonText;
	bool Swap = false;	
	Button* shop_spawnButton; 
public:
	Shop();
	void init();
	virtual ~Shop();
	virtual void Update(float deltaTime) override;
	void Reroll();
	void Spawn(); 
	void MakeText(int order,int count);
	void SetOtherUI(GameObject* combination) {this->combination = combination;}
	int TowerNameToID(std::wstring name);
	void ChangeButton();
	Button* GetSwapButton() { return shop_spawnButton; }

};

