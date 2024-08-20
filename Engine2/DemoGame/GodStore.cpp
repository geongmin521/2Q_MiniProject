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
	Make(Image)(L"UI/Pop_up/Popup_SpecialReward.png").setParent(this->transform);

	//각 보상 버튼 
	Make(Button)(L"Frame", [this]() {if (cost[0] <= gameManager->GetGold()) btn->SetInteractive(true); compensationId = 1; TimeScaleIsClick(0); }, ButtonType::Active).
		AddText(L"축복",50,0,-110).
		AddText(L"신앙심 20", 50, 0, 120).
		AddText(L"일반 유물", 50, 0, 150).
		setPos_Parent({-810, -110}, transform).
		Get(CompensationBtn[0]);
	Make(Image)(L"UI/Icon/special_item_001.png").setPos_Parent({ -810, -110 }, transform);
	Make(Button)(L"Frame", [this]() {if (cost[1] <= gameManager->GetGold()) btn->SetInteractive(true); compensationId = 2; TimeScaleIsClick(1); }, ButtonType::Active).
		AddText(L"성물", 50,0,-110).
		AddText(L"신앙심 40", 50, 0, 120).
		AddText(L"특별 유물", 50, 0, 150).
		setPos_Parent({ 0, -110 },transform).
		Get(CompensationBtn[1]);
	Make(Image)(L"UI/Icon/special_item_002.png").setPos_Parent({ 0, -110 }, transform);
	Make(Button)(L"Frame", [this]() {if (cost[2] <= gameManager->GetGold()) btn->SetInteractive(true); compensationId = 3; TimeScaleIsClick(2); }, ButtonType::Active).
		AddText(L"고해성사", 50,0,-110).
		AddText(L"신앙심 50", 50, 0, 120).
		AddText(L"소환기회 + 1", 50, 0, 150).
		setPos_Parent({ 810, -110 },transform).
		Get(CompensationBtn[2]);
	Make(Image)(L"UI/Icon/special_item_003.png").setPos_Parent({ 810, -110 }, transform);
	//이거 클리하면 강조된걸로 변하는거지? 
	//선택완료 
	Make(Button)(L"Pray", [this]() {GetCompensation(), SetActive(false); }).setPos_Parent({200, 400}, transform).Get<Button>(btn);
	//나가기 버튼
	Make(Button)(L"Return", [this]() { SetActive(false); }).setPos_Parent({ -200, 400 }, this->transform);
	btn->SetInteractive(false); //기도하기 버튼도 보상줄게 있어야 나갈수있는거지? 
	SetActive(false);
	for (int i = 0; i < 3; i++)
		CompensationBtn[i]->SetIsEnable(false);
}

GodStore::~GodStore()
{
}

void GodStore::GetCompensation() //돈이 없으면확실히 비활성화 상태로 만드는게 좋을듯?
{
	if (gameManager->GetGold() < cost[compensationId - 1]) //돈없으면 리턴
		return;
	if (compensationId == 1) {
		//유물보상?  // 유물 보상나오는거되고. .//이건 일반 보상인가? 
		gameManager->Compensation(false);
	}
	else if(compensationId == 2){
		//보상선택 +1이 뭐였지? //보상띄우는거였고.. 
		gameManager->Compensation(true);
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

void GodStore::TimeScaleIsClick(int num)
{
	for (int i = 0; i < 3; i++)
	{
		if (i == num)
			continue;
		CompensationBtn[i]->SetIsEnable(false);
	}
}