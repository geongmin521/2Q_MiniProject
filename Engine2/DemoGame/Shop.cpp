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
	Make(Image)(L"BigBack.png").setScale({ 2,2 }).setParent(transform);
	float LPad = -200; 
	for (int i = 0; i < 5; i++)//아이콘
		Make(Image)(L"Crossbow.png").setPos_Parent({ LPad + i * 130 , -100 }, transform).Get<Image>(Icons);
	for (int i = 0; i < 5; i++)//리롤 잠그기
		Make(Button)(L"smallBack.png", [i, this]() { isLock[i] = !isLock[i]; }).setPos_Parent_Text({ LPad + i * 130, 0 }, transform, L"Lock", 20);
	//리롤 버튼	 //같은색깔 끼리 모이니까 이쁘긴한데 가독성은 뭐가 나을려나..
	//조합표 확인 버튼
	//소환하기 버튼
	//소환하기 버튼
	//리롤 횟수 텍스트박스
	Make(Button)(L"ImageBack.png", std::bind(&Shop::Reroll, this)).setPos_Parent_Text({ LPad + 250, 100 }, transform, L"전체리롤", 30).GetComponent<D2DFont>(rerollButtonText);
	Make(Button)(L"ImageBack.png", [this]() {combination->SetActive(true); }).setPos_Parent_Text({ LPad + 650, +100 }, transform, L"조합식", 30);
	Make(Button)(L"ImageBack.png", std::bind(&Shop::Spawn, this)).setPos_Parent_Text({ LPad + 650, +200 }, transform, L"소환하기", 30);
	Make(Image)(L"ImageBack.png").setPos_Parent_Text({ LPad + 250, +200 }, transform, L"", 20).GetComponent<D2DFont>(compensationText);
	Make(Image)(L"ImageBack.png").setPos_Parent_Text({ LPad + 250, +300 }, transform, L"리롤 가능 횟수" + std::to_wstring(reroll), 20).GetComponent<D2DFont>(rerollText);
	Make(Button)(L"UI.png", []() {}).setPosition(WinSizeXYAdd(-200, -100)).AddText(L"적 소환", 50).Get<Button>(shop_spawnButton);//상점_스폰 버튼- 상점으로 이전하기

	for (int i = 0; i < 4; i++) //타워 인벤 //이것도 그냥 샵한테 줘버릴까? //그래도 될거같지? //샵도 그럼 엄청 거대해지긴함.. 
		Make(Container)().setPosition({ 100.0f + i * 150, WinSizeY - 100 }).Get<Container>(Containers);
	SetActive(false); ChangeButton(); shop_spawnButton->SetInteractive(true);
}

void Shop::init()
{
	for (int i = 0; i < 5; i++)
	{
		isLock[i] = false;
	}
	reroll = 5;
	rerollText->SetDialog(L"리롤 가능 횟수" + std::to_wstring(reroll));
}

Shop::~Shop()
{
}

void Shop::Update(float deltaTime)
{
	if (Swap == false)
	{
		int count = 0;
		for (int i = 0; i < Containers.size(); i++)
		{
			if (Containers[i]->isContain == false)
				count++;
		}
		if (count == 4)  //타워가 전부 비어있는지 검사
		{
			shop_spawnButton->SetInteractive(true);
		}
		else
		{
			shop_spawnButton->SetInteractive(false);
		}
	}
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

void Shop::ChangeButton() //샵과 관련된 로직이 여기 많은데.. 이걸 전부 샵으로 이동시킬수있을거같긴함.. 그러고 나면 담는애들은 전부 UI에 불고할거고. 
{
	if (Swap) //버튼 특성상 이걸 알고있는게 맞을까 아니면 게임 매니저한테 넘길까.. 
	{
		shop_spawnButton->SetListener([this]() { gameManager->events["SpawnEnemy"](); ChangeButton(); }); //이렇게 되면 스포너를 얘가 들고있는게 맞나? 아니면 게임 매니저한테 맡길까? 
		shop_spawnButton->GetComponent<D2DFont>()->SetDialog(L"적소환");
	}
	else
	{
		shop_spawnButton->SetListener([this]() { SetActive(true); Reroll(); ChangeButton(); });
		shop_spawnButton->GetComponent<D2DFont>()->SetDialog(L"타워소환");
	}
	Swap = !Swap;
	shop_spawnButton->SetInteractive(false);
}