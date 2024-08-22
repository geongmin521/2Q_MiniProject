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
	//���
	Make(Image)(L"UI/Pop_up/Popup_SpecialReward.png").setParent(this->transform);
	std::wstring name[3] = { L"�ູ" ,L"����" ,L"���ؼ���" };
	std::wstring costtext[3] = { L"�žӽ� 20" ,L"�žӽ� 40" ,L"�žӽ� 50" };
	std::wstring compensation[3] = { L"�Ϲ� ����",L"Ư�� ����" , L"��ȯ��ȸ + 1" };

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

	//���ÿϷ� 
	Make(Button)(L"Pray", [this]() {GetCompensation(), SetActive(false);
	Music::soundManager->PlayMusic(Music::eSoundList::ButtonClick, Music::eSoundChannel::Effect2); }).setPos_Parent({ 300, 400 }, transform).Get<Button>(btn);
	//������ ��ư
	Make(Button)(L"Return", [this]() { SetActive(false);
	Music::soundManager->PlayMusic(Music::eSoundList::RewardClose, Music::eSoundChannel::Effect1); }).setPos_Parent({ -300, 400 }, this->transform);
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