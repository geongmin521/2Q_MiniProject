#include "pch.h"
#include "GodStore.h"
#include "Factory.h"
#include "Image.h"
#include "Button.h"
#include "GameManager.h"

GodStore::GodStore()
{
	renderOrder += 100;
	//배경
	Make(Image)(L"BigBack.png").setScale({2,2}).setParent(this->transform);
	//나가기 버튼
	Make(Button)(L"smallBack.png", [this]() { SetActive(false); }).setPos_Parent({500, -400},this->transform);
	//각 보상 버튼 
	Make(Button)(L"smallBack.png", [this]() {if(cost[0] <= gameManager->GetGold()) btn->SetInteractive(true); compensationId = 1; }).
		AddText(L"구원",20,0,-100).
		AddText(L"신앙심 10", 20, 0, 100).
		AddText(L"유물구매?", 20, 0, 150).
		setPos_Parent({-100, 0}, transform);
	Make(Button)(L"smallBack.png", [this]() {if (cost[1] <= gameManager->GetGold()) btn->SetInteractive(true); compensationId = 2;}).
		AddText(L"특전",20,0,-100).
		AddText(L"신앙심 30", 20, 0, 100).
		AddText(L"보상선택 + 1", 20, 0, 150).
		setPos_Parent({ 0, 0 },transform);
	Make(Button)(L"smallBack.png", [this]() {if (cost[2] <= gameManager->GetGold()) btn->SetInteractive(true); compensationId = 3; }).
		AddText(L"고해성사",20,0,-100).
		AddText(L"신앙심 50", 20, 0, 100).
		AddText(L"소환기회 + 1", 20, 0, 150).
		setPos_Parent({ 100, 0 },transform);
	//선택완료 
	Make(Button)(L"smallBack.png", [this]() {GetCompensation(), SetActive(false); }).AddText(L"선택완료",20).setPos_Parent({200, 200}, transform).Get<Button>(btn);
	btn->SetInteractive(false);
	SetActive(false);
}

GodStore::~GodStore()
{
}

void GodStore::GetCompensation()
{
	if (compensationId == 1) {
		//유물보상? 
		
	}
	else if(compensationId == 2){
		//보상선택 +1이 뭐였지? 
	}
	else if(compensationId == 3){ //오케이상점도 다만들었고.. 안에 함수만 채워넣으면될거같고
		gameManager->chance++;
	}
	else
	{
		return;
	}
	gameManager->UseGold(cost[compensationId-1]);
	SetActive(false);
}
