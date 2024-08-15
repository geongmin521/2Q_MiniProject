#include "pch.h"
#include "GodStore.h"
#include "Factory.h"
#include "Image.h"
#include "Button.h"

GodStore::GodStore()
{
	renderOrder += 100;
	//배경
	Make(Image)(L"BigBack.png").setScale({2,2}).setParent(this->transform);
	//나가기 버튼
	Make(Button)(L"smallBack.png", [this]() { SetActive(false); }).setPos_Parent({500, -400},this->transform);
	//각 보상 버튼 
	Make(Button)(L"smallBack.png", [this]() {btn->SetInteractive(true); compensationId = 1; }).setPos_Parent({ -100, 0 },transform);
	Make(Button)(L"smallBack.png", [this]() {btn->SetInteractive(true); compensationId = 2; }).setPos_Parent({ 0, 0 },transform);
	Make(Button)(L"smallBack.png", [this]() {btn->SetInteractive(true); compensationId = 3; }).setPos_Parent({ 100, 0 },transform);
	//선택완료 
	Make(Button)(L"smallBack.png", [this]() {GetCompensation(), SetActive(false); }).setPos_Parent({200, 200},transform).Get<Button>(btn); 
	btn->SetInteractive(false);
	SetActive(false);
}

GodStore::~GodStore()
{
}

void GodStore::GetCompensation()
{
	if (compensationId == 1){

	}
	else if(compensationId == 2){

	}
	else if(compensationId == 3){
	}
}
