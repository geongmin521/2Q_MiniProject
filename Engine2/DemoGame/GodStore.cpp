#include "pch.h"
#include "GodStore.h"
#include "Factory.h"
#include "Image.h"
#include "Button.h"
#include "GameManager.h"

GodStore::GodStore()
{
	renderOrder += 100;
	//���
	Make(Image)(L"BigBack.png").setScale({2,2}).setParent(this->transform);
	//������ ��ư
	Make(Button)(L"smallBack.png", [this]() { SetActive(false); }).setPos_Parent({500, -400},this->transform);
	//�� ���� ��ư 
	Make(Button)(L"smallBack.png", [this]() {if(cost[0] <= gameManager->GetGold()) btn->SetInteractive(true); compensationId = 1; }).
		AddText(L"����",20,0,-100).
		AddText(L"�žӽ� 10", 20, 0, 100).
		AddText(L"��������?", 20, 0, 150).
		setPos_Parent({-100, 0}, transform);
	Make(Button)(L"smallBack.png", [this]() {if (cost[1] <= gameManager->GetGold()) btn->SetInteractive(true); compensationId = 2;}).
		AddText(L"Ư��",20,0,-100).
		AddText(L"�žӽ� 30", 20, 0, 100).
		AddText(L"������ + 1", 20, 0, 150).
		setPos_Parent({ 0, 0 },transform);
	Make(Button)(L"smallBack.png", [this]() {if (cost[2] <= gameManager->GetGold()) btn->SetInteractive(true); compensationId = 3; }).
		AddText(L"���ؼ���",20,0,-100).
		AddText(L"�žӽ� 50", 20, 0, 100).
		AddText(L"��ȯ��ȸ + 1", 20, 0, 150).
		setPos_Parent({ 100, 0 },transform);
	//���ÿϷ� 
	Make(Button)(L"smallBack.png", [this]() {GetCompensation(), SetActive(false); }).AddText(L"���ÿϷ�",20).setPos_Parent({200, 200}, transform).Get<Button>(btn);
	btn->SetInteractive(false);
	SetActive(false);
}

GodStore::~GodStore()
{
}

void GodStore::GetCompensation()
{
	if (compensationId == 1) {
		//��������? 
		
	}
	else if(compensationId == 2){
		//������ +1�� ������? 
	}
	else if(compensationId == 3){ //�����̻����� �ٸ������.. �ȿ� �Լ��� ä��������ɰŰ���
		gameManager->chance++;
	}
	else
	{
		return;
	}
	gameManager->UseGold(cost[compensationId-1]);
	SetActive(false);
}
