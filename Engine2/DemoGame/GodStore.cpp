#include "pch.h"
#include "GodStore.h"
#include "Factory.h"
#include "Image.h"
#include "Button.h"
#include "GameManager.h"
#include "Music.h"

GodStore::GodStore()
{
	renderOrder += 100;
	//배경
	Make(Image)(L"UI/Pop_up/Popup_SpecialReward.png").setParent(this->transform);
	std::wstring name[3] = { L"축복" ,L"성물" ,L"고해성사" };
	std::wstring costtext[3] = { L"신앙심 20" ,L"신앙심 40" ,L"신앙심 50" };
	std::wstring compensation[3] = { L"일반 유물",L"특별 유물" , L"소환기회 + 1" };

	for (int i = 0; i < 3; i++)
	{
		Make(Button)(L"Frame", [this,i]() {if (cost[i] <= gameManager->GetGold()) btn->SetInteractive(true); compensationId = i+1; TimeScaleIsClick(i); }, ButtonType::Active).
			AddText(name[i], 50, 0, -110).
			AddText(costtext[i], 50, 0, 120).
			AddText(compensation[i], 50, 0, 150).
			setPos_Parent({ -811.0f + (i * 812), -110 }, transform).
			Get(CompensationBtn[i]);
	}
	for(int i=0;i< 3;i++)
		Make(Image)(L"UI/Icon/special_item_00" + std::to_wstring(i + 1) + L".png").AddRenderOrder(10).setScale({0.75,0.75}).setPos_Parent({ -810.0f + (i * 810), -110 }, transform).setBoundBox(0, 0);

	//선택완료 
	Make(Button)(L"Pray", [this]() {GetCompensation(), SetActive(false);
	Music::soundManager->PlayMusic(Music::eSoundList::ButtonClick, Music::eSoundChannel::Effect2); }).setPos_Parent({ 300, 400 }, transform).Get<Button>(btn);
	//나가기 버튼
	Make(Button)(L"Return", [this]() { SetActive(false);
	Music::soundManager->PlayMusic(Music::eSoundList::RewardClose, Music::eSoundChannel::Effect1); }).setPos_Parent({ -300, 400 }, this->transform);
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

void GodStore::Enable()
{
	for (int i = 0; i < 3; i++)
		CompensationBtn[i]->SetIsEnable(false);
	btn->SetInteractive(false);
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