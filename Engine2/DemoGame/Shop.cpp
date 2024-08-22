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
#include "Dotween.h"

#include "D2DEffectManager.h"
#include "CrossFadeEffect.h"

#include "Music.h"

Shop::Shop() 
{
	Make(GameObject)().setParent(transform).Get(child);
	ImagePath = { L"Crossbow_shadow.png",L"holywater_shadow.png",L"anchor_shadow.png",L"Holycross_shadow.png",L"Skul_shadow.png" };
	TowerName = {L"석궁타워", L"성수타워", L"말뚝타워", L"힐타워" };
	Make(Image)(L"UI/Pop_up/popup.png").AddText(L"", 30, 30, 175, &compensationText).AddText(L"", 50, 443, -210, &goldText).setParent(child->transform);
	float LPad = -960; 
	for (int i = 0; i < 5; i++)//아이콘
		Make(Image)(L"UI/Icon/Crossbow_shadow.png").setPos_Parent({ LPad + i * 480 , -200 }, child->transform).Get<Image>(Icons);
	for (int i = 0; i < 5; i++)//리롤 잠그기
		Make(Button)(L"lock", [i, this]() { isLock[i] = !isLock[i];
		if (isLock[i])
			Music::soundManager->PlayMusic(Music::eSoundList::Lock, Music::eSoundChannel::Effect1);
		else
			Music::soundManager->PlayMusic(Music::eSoundList::UnLock, Music::eSoundChannel::Effect1);}, ButtonType::Active).setPos_Parent({ LPad + i * 480, 130 }, child->transform).Get(lockButton[i]);
	//리롤 버튼	 //같은색깔 끼리 모이니까 이쁘긴한데 가독성은 뭐가 나을려나..
	//조합표 확인 버튼
	//소환하기 버튼
	//소환하기 버튼
	//리롤 횟수 텍스트박스
	//상점 활성화 버튼
	Make(Button)(L"Reroll", std::bind(&Shop::Reroll, this)).AddText(L"",40,50, 0, &rerollButtonText).AddText(L"", 50, 50, 0, &rerollText).setPos_Parent({0, 320}, child->transform);
	Make(Button)(L"Create", [this]() {combination->SetActive(true); }).setScale({ 1.4f,1.4f }).setPos_Parent({ -980, +400 }, child->transform);
	Make(Button)(L"summon", std::bind(&Shop::Spawn, this)).setPos_Parent({980, +400 }, child->transform);
	Make(Button)(L"CS", []() {}).setPosition(WinSizeXYAdd(-200, -100)).setScale({ 0.9,0.9 }).Get<Button>(shop_spawnButton);

	for (int i = 0; i < 4; i++) //타워 인벤
		Make(Container)(i).setPosition({ 475.0f + i * 150, WinSizeY - 100 }).Get<Container>(Containers);
	child->SetActive(false); ChangeButton(ButtonState::TowerSpawn); shop_spawnButton->SetInteractive(true);

}

void Shop::init() //여기가 처음에 들어오는데네
{
	for (int i = 0; i < 5; i++)
	{
		isLock[i] = false;
	}
	for (int i = 0; i < 5; i++)
		lockButton[i]->SetIsEnable(true);
	reroll = 2;
	rerollText->SetDialog(std::to_wstring(reroll));
}

Shop::~Shop()
{
}

void Shop::Update(float deltaTime) 
{
	__super::Update(deltaTime);
	if (gameManager->chance <= 0)
		ChangeButton(ButtonState::EnemySpawn);
	else
		ChangeButton(ButtonState::TowerSpawn); 
	goldText->SetDialog(L"신앙심:" + std::to_wstring(gameManager->GetGold()));
	if (curState == ButtonState::EnemySpawn) 
	{
		int count = 0;
		for (int i = 0; i < Containers.size(); i++)
		{
			if (Containers[i]->isContain == false)
				count++;
		}
		if (count == 4 && gameManager->isBattle == false)  //타워가 전부 비어있는지 검사
		{
			shop_spawnButton->SetInteractive(true);	
//			TowerBase* tower = dynamic_cast<TowerBase*>(Pools::GetInstance().get()->PopPool(12));
//			tower->Init({ 0,0 });
		}
		else
		{
			shop_spawnButton->SetInteractive(false);
		}
	}
	else if (curState = ButtonState::TowerSpawn)
	{
		if (child->GetActive() == false) //상점이 꺼져있는상태면 활성화
			shop_spawnButton->SetInteractive(true);	
	}
	
	if (gameManager->isBattle == true)
	{
		D2DEffectManager::GetInstance()->FindIEffect<CrossFadeEffect>(L"MapFade")->isFadeIn = false;
	}
}

void Shop::Reroll() 
{
	if (reroll <= 0)
		rerollButtonText->SetDialog(L" - 10 신앙심"); 
	if(reroll > 0)
		reroll--;
	else if(gameManager->GetGold() >= 10)
	{
		gameManager->UseGold(10);
	}
	else
		return;

	for (int i = 0; i < Icons.size(); i++) //
	{
		if (isLock[i] == true)
			continue;
		new DOTween(Icons[i]->transform->relativeScale.x, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 1.f, 0.2, 1); 
		new DOTween(Icons[i]->transform->relativeScale.y, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 1.f, 0.2, 1);
	} 
	compensationList.clear();
	Text = L""; //텍스트 초기화
	
	rerollText->SetDialog(std::to_wstring(reroll));
	for (int i = 0; i < 5; i++)
	{
		if (isLock[i])
			continue;
		int random = Utility::RandomBetween(0, ImagePath.size() - 1);
		Icons[i]->ChangeImage(L"../Data/Image/UI/Icon/" + ImagePath[random]);
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
	else if (count[4] == 5)//히든타워조합
	{
		Text = L"히든타워";
		compensationText->SetDialog(Text);
		compensationList = { 12 };
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
		if (dynamic_cast<TowerBase*>(tower) != nullptr)
		{
			dynamic_cast<TowerBase*>(tower)->Init(Containers[inven]->transform->GetWorldLocation());
			Containers[inven]->OnDrop(tower);			
		}
		
		if (var != 0 && var != 3 && var != 6 && var != 9)
		{
			Music::soundManager->PlayMusic(Music::eSoundList::TowerUpgrade, Music::eSoundChannel::Effect1);
		}
		inven++;
	}
	compensationList.clear(); 
	child->SetActive(false);
}

void Shop::MakeText(int order, int count)
{	
	if (count == 2)
	{
		if (Text != L"") 
			Text += L"+";
		compensationList.push_back(order * 3 + 0);
		Text += L"1성" + TowerName[order] + L"1개"; 
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

void Shop::ChangeButton(ButtonState state)
{
	if (curState == state)
		return;
	curState = state;

	if (curState == ButtonState::EnemySpawn)
	{
		shop_spawnButton->name = "Combat";
		shop_spawnButton->GetComponent<Bitmap>()->LoadD2DBitmap(L"../Data/Image/UI/Button/Combat_Nomal.png");
		shop_spawnButton->SetListener([this]() { gameManager->events[Event::SpawnEnemy](); });
	}
	else if(curState == ButtonState::TowerSpawn) //이게 가독성이 좀더좋은듯?
	{
		shop_spawnButton->name = "CS";
		shop_spawnButton->GetComponent<Bitmap>()->LoadD2DBitmap(L"../Data/Image/UI/Button/CS_Nomal.png");
		shop_spawnButton->SetListener([this]() { child->SetActive(true); Reroll(); init(); gameManager->chance--; });
	}	
	shop_spawnButton->SetInteractive(false);
}


