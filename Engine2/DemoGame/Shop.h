#pragma once
#include "../D2DEngine/UI.h"

class Image;
class Container;
class Combination;
class Shop: public UI //샵클래스? 사실 그냥 UI오브젝트들의 집합이자 상점에 필요한 함수들의 집합임
{
private:
	bool isLock[5];
	int Id[5]; 
	int reroll;
	std::vector<GameObject*> subUi;			
	std::vector<Image*> Icons;				
	std::vector<std::wstring> ImagePath;	
	std::vector<std::wstring> TowerName;	
	std::vector<int> compensationList; //보상으로 받아야하는 타워의 아이디를 저장하기
	std::wstring Text;
	std::vector<Container*> Containers; //여기에 들고는있지만.. 생성은 외부에서 해야할듯? 
	Combination* combination;
public:

	Shop();
	virtual ~Shop();
	void Reroll();
	void Spawn(); //여기서 조합식 처리하는것도 만들어야하고.. 
	void MakeText(std::wstring name,int count);
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
	void SetOtherUI(std::vector<Container*> container, Combination* combination) { this->Containers = container; this->combination = combination;}
	int TowerNameToID(std::wstring name); //정말이러긴 싫지만 지금은 생각이안난다.. 

};

