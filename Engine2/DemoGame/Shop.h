#pragma once
#include "UIPanel.h"

class Image;
class Container;
class Combination;
class EnemySpawner;
class Shop: public UIPanel 
{
private:
	bool isLock[5];
	int Id[5]; 
	int reroll;
	std::vector<Image*> Icons;				
	std::vector<std::wstring> ImagePath;	
	std::vector<std::wstring> TowerName;	
	std::vector<int> compensationList; //보상으로 받아야하는 타워의 아이디를 저장하기
	std::wstring Text;
	std::vector<Container*> Containers; //여기에 들고는있지만.. 생성은 외부에서 해야할듯? 
	Combination* combination;

	//직접 참조시키지말고.. 나중에 이벤트가 같은걸로빼서 알려줘도 좋을거같은데?
	
public:
	EnemySpawner* spawner;
	Shop();
	virtual ~Shop();
	void Reroll();
	void Spawn(); //여기서 조합식 처리하는것도 만들어야하고.. 
	void MakeText(int order,int count); //석궁,성수,말뚝,십자가 // {L"석궁타워", L"성수타워", L"말뚝타워", L"힐타워" };
	void SetOtherUI(std::vector<Container*> container, Combination* combination) { this->Containers = container; this->combination = combination;}
	int TowerNameToID(std::wstring name); //정말이러긴 싫지만 지금은 생각이안난다.. 

};

