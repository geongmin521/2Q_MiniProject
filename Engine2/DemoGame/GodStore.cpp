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
	Make(Image)(L"UI/Pop_up/Popup_SpecialReward.png").setParent(this->transform);

	//�� ���� ��ư 
	Make(Button)(L"Frame", [this]() {if (cost[0] <= gameManager->GetGold()) btn->SetInteractive(true); compensationId = 1; TimeScaleIsClick(0); }, ButtonType::Active).
		AddText(L"�ູ",50,0,-110).
		AddText(L"�žӽ� 20", 50, 0, 120).
		AddText(L"�Ϲ� ����", 50, 0, 150).
		setPos_Parent({-810, -110}, transform).
		Get(CompensationBtn[0]);
	Make(Image)(L"UI/Icon/special_item_001.png").setPos_Parent({ -810, -110 }, transform);
	Make(Button)(L"Frame", [this]() {if (cost[1] <= gameManager->GetGold()) btn->SetInteractive(true); compensationId = 2; TimeScaleIsClick(1); }, ButtonType::Active).
		AddText(L"����", 50,0,-110).
		AddText(L"�žӽ� 40", 50, 0, 120).
		AddText(L"Ư�� ����", 50, 0, 150).
		setPos_Parent({ 0, -110 },transform).
		Get(CompensationBtn[1]);
	Make(Image)(L"UI/Icon/special_item_002.png").setPos_Parent({ 0, -110 }, transform);
	Make(Button)(L"Frame", [this]() {if (cost[2] <= gameManager->GetGold()) btn->SetInteractive(true); compensationId = 3; TimeScaleIsClick(2); }, ButtonType::Active).
		AddText(L"���ؼ���", 50,0,-110).
		AddText(L"�žӽ� 50", 50, 0, 120).
		AddText(L"��ȯ��ȸ + 1", 50, 0, 150).
		setPos_Parent({ 810, -110 },transform).
		Get(CompensationBtn[2]);
	Make(Image)(L"UI/Icon/special_item_003.png").setPos_Parent({ 810, -110 }, transform);
	//�̰� Ŭ���ϸ� �����Ȱɷ� ���ϴ°���? 
	//���ÿϷ� 
	Make(Button)(L"Pray", [this]() {GetCompensation(), SetActive(false); }).setPos_Parent({200, 400}, transform).Get<Button>(btn);
	//������ ��ư
	Make(Button)(L"Return", [this]() { SetActive(false); }).setPos_Parent({ -200, 400 }, this->transform);
	btn->SetInteractive(false); //�⵵�ϱ� ��ư�� �����ٰ� �־�� �������ִ°���? 
	SetActive(false);
	for (int i = 0; i < 3; i++)
		CompensationBtn[i]->SetIsEnable(false);
}

GodStore::~GodStore()
{
}

void GodStore::GetCompensation() //���� ������Ȯ���� ��Ȱ��ȭ ���·� ����°� ������?
{
	if (gameManager->GetGold() < cost[compensationId - 1]) //�������� ����
		return;
	if (compensationId == 1) {
		//��������?  // ���� ���󳪿��°ŵǰ�. .//�̰� �Ϲ� �����ΰ�? 
		gameManager->Compensation(false);
	}
	else if(compensationId == 2){
		//������ +1�� ������? //������°ſ���.. 
		gameManager->Compensation(true);
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

void GodStore::TimeScaleIsClick(int num)
{
	for (int i = 0; i < 3; i++)
	{
		if (i == num)
			continue;
		CompensationBtn[i]->SetIsEnable(false);
	}
}