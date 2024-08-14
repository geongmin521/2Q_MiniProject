#include "pch.h"
#include "D2DRenderer.h"
#include "Pools.h"
#include "Transform.h"
#include "Factory.h"
#include "Shop.h"
#include "Image.h"
#include "Container.h"
#include "Combination.h"
#include "EnemySpawner.h"
#include "Button.h"
#include "TowerBase.h"
#include "D2DFont.h"
#include "GameManager.h"

Shop::Shop() 
{
	ImagePath = { L"Crossbow.png",L"Water.png",L"Pile.png",L"HolyCross.png",L"vampire.png" };
	TowerName = {L"석궁타워", L"성수타워", L"말뚝타워", L"힐타워" };
	Factory().createObj<Image>(L"BigBack.png").setPosition(WinHalfSizeXY).setScale({ 2,2 }).setParent(this->transform);
	float LeftPadding = 700; 
	for (int i = 0; i < 5; i++)//아이콘
		Icons.push_back(Factory().createObj<Image>(L"Crossbow.png").setPosition({ LeftPadding + i * 130 ,WinHalfSizeY - 200 }).setParent(this->transform).Get<Image>());
	for (int i = 0; i < 5; i++)//리롤 잠그기
		Factory().createObj<Button>(L"smallBack.png", [i, this]() { isLock[i] = !isLock[i]; }).setPosition({ LeftPadding + i * 130, WinHalfSizeY - 100 }).setParent(this->transform).AddText(L"Lock", 20);
	
	rerollButtonText = Factory().createObj<Button>(L"ImageBack.png", std::bind(&Shop::Reroll, this)).setPosition({ LeftPadding + 250, WinHalfSizeY + 100 }).setParent(this->transform).AddText(L"전체리롤", 30).Get()->GetComponent<D2DFont>();
	//보상 텍스트박스 
	compensationText = Factory().createObj<Image>(L"ImageBack.png").setPosition({ LeftPadding + 250, WinHalfSizeY + 200 }).setParent(this->transform).AddText(L"", 20).Get()->GetComponent<D2DFont>();
	//리롤가능한 횟수를 출력하는 텍스트박스
	rerollText = Factory().createObj<Image>(L"ImageBack.png").setPosition({ LeftPadding + 250, WinHalfSizeY + 300 }).setParent(this->transform).AddText(L"리롤 가능 횟수" + std::to_wstring(reroll), 20).Get()->GetComponent<D2DFont>();
	//조합표 확인 버튼
	Factory().createObj<Button>(L"ImageBack.png", [this]() {combination->SetActive(true); }).setPosition({LeftPadding + 650, WinHalfSizeY + 100}).setParent(this->transform).AddText(L"조합식", 30); 
	//소환하기 버튼
	Factory().createObj<Button>(L"ImageBack.png", std::bind(&Shop::Spawn, this)).setPosition({ LeftPadding + 650, WinHalfSizeY + 200 }).setParent(this->transform).AddText(L"소환하기", 30);

	SetActive(false); 
}
void Shop::init()
{
	reroll = 5;
	rerollText->SetDialog(L"리롤 가능 횟수" + std::to_wstring(reroll));
}

Shop::~Shop()
{
}

void Shop::Reroll() 
{
	if (reroll <= 0)
		rerollButtonText->SetDialog(L"전체리롤 -10 신앙심");
	
	if(reroll > 0)
		reroll--;
	else if(gameManager->gold > 10) 
	{
		gameManager->gold -= 10;
	}
	else
		return;

	compensationList.clear();
	Text = L""; //텍스트 초기화
	
	rerollText->SetDialog(L"리롤 가능 횟수" +std::to_wstring(reroll));
	for (int i = 0; i < 5; i++)
	{
		if (isLock[i])
			continue;
		int random = Utility::RandomBetween(0, ImagePath.size() - 1);
		Icons[i]->ChangeImage(L"../Data/Image/" + ImagePath[random]);
		Id[i] = random;
	}

	int count[5] = { 0,0,0,0,0 };

	for (auto var : Id)
		count[var]++;

	if (count[0] == 1 && count[1] == 1 && count[2] == 1 && count[3] == 1 && count[4] == 1) //예외적인 스페셜조합
	{
		Text = L"모든 타워 1성";
		compensationText->SetDialog(Text);
		compensationList = { 0,3,6,9 };
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		MakeText(i, count[i]);
	}
	if (Text == L"")
		Text = L"꽝";
	compensationText->SetDialog(Text);
}

void Shop::Spawn()
{
	int inven = 0;
	for (auto var : compensationList)
	{	
		GameObject* tower = Pools::GetInstance().get()->PopPool(var);  
		if (tower != nullptr)
		{
			dynamic_cast<TowerBase*>(tower)->Init(Containers[inven]->transform->GetWorldLocation());
			Containers[inven]->OnDrop(tower); 
		}
		
		inven++;
	}
	compensationList.clear(); 
	SetActive(false);
}

void Shop::MakeText(int order, int count)
{	
	if (count == 2)
	{
		if (Text != L"") 
			Text += L"+";
		compensationList.push_back(order * 3 + 0);
		compensationList.push_back(order * 3 + 0);
		Text += L"1성" + TowerName[order] + L"2개"; 
	}
	else if (count == 3)
	{
		if (Text != L"") 
			Text += L"+";
		compensationList.push_back(order * 3 + 1);
		Text += L"2성" + TowerName[order];
	}
	else if (count == 4)
	{
		if (Text != L"")
			Text += L"+";
		compensationList.push_back(order * 3 + 1);
		compensationList.push_back(order * 3 + 1);
		Text += L"2성" + TowerName[order] + L"2개"; 
	}
	else if (count == 5)
	{
		if (Text != L"") 
			Text += L"+";
		compensationList.push_back(order * 3 + 2);
		Text += L"3성" + TowerName[order];
	}
} 

int Shop::TowerNameToID(std::wstring name)
{
	for (int i = 0; i < TowerName.size(); i++)
	{
		if (TowerName[i] == name)
			return i * 3;
	}
}
