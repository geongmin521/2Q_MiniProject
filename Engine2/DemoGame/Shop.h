#pragma once
#include "UI.h"

enum  ButtonState
{
	EnemySpawn,
	TowerSpawn
};

class Image;
class Container;
class D2DFont;
class Button;
class Transform;
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
	Button* shop_spawnButton; 
	ButtonState curState = EnemySpawn;
	GameObject* child; //자식을 관리하기 위한 트랜스폼

	float test;
	bool effectCheck = false;

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
	void ChangeButton(ButtonState state);
	Button* GetSwapButton() { return shop_spawnButton; }

};

