#include "pch.h"
#include "BattleWorld.h"
#include "Camera.h"
#include "Button.h"
#include "Factory.h"
#include "Shop.h"
#include "ShowWave.h"
#include "Combination.h"
#include "Container.h"
#include "TimeSystem.h"
#include "DataManager.h"
#include "Transform.h"
#include "EnemySpawner.h"
#include "GameManager.h"
#include "Image.h"
#include "Map.h"
#include "D2DFont.h"
#include "GameOver.h"
#include "CollisionManager.h"
#include "InputSystem.h"
#include "Compensation.h"

#include "Light.h" // 라이트 테스트


BattleWorld::BattleWorld()
{
}

BattleWorld::~BattleWorld()
{
}

void BattleWorld::MakeObject() 
{
	Factory().createObj<Image>(L"afternoon.png").setScale({ 0.75f,0.75f }).setRenderOrder(-100).setPosition(WinHalfSizeXY); //배경
	spwaner = Factory().createObj<EnemySpawner>().Get<EnemySpawner>(); 
	Factory().createObj<Map>();
	MakeUI();

	DataManager::GetInstance().get()->ChoseWave();
	showWave->Show(); 
}

void BattleWorld::MakeUI() 
{
	WaveCount = Factory().createObj<Image>(L"UI.png").setPosition({ WinHalfSizeX, 100 }).AddText(L"Wave 1", 40).Get<Image>(); //웨이브카운트
	Factory().createObj<Button>(L"smallBack.png",[]() {timeManager->SetTimeScale(0); }).setPosition({ WinSizeX - 400, 200 }); //시간 조절 버튼
	Factory().createObj<Button>(L"smallBack.png",[]() {timeManager->SetTimeScale(1); }).setPosition({ WinSizeX - 300, 200 });
	Factory().createObj<Button>(L"smallBack.png",[]() {timeManager->SetTimeScale(2); }).setPosition({ WinSizeX - 200, 200 });

	for (int i = 0; i < 4; i++) //타워 인벤
	{
		TowerInventory.push_back(Factory().createObj<Container>().setPosition({ 100.0f + i * 150, WinSizeY - 100 }).Get<Container>());
	}
		
	combination = Factory().createObj<Combination>().Get<Combination>();
	shop = Factory().createObj<Shop>().Get<Shop>(); shop->SetOtherUI(TowerInventory, combination); shop->spawner = spwaner;
	showWave = Factory().createObj<ShowWave>().Get<ShowWave>();
	compensation = Factory().createObj<Compensation>().Get<Compensation>();
	
	Factory().createObj<Button>(L"UI.png", [this]() { combination->SetActive(true); }).setPosition({ WinSizeX - 600, WinSizeY - 100 }).AddText(L"조합식", 50); //조합표
	shop_spawnButton = Factory().createObj<Button>(L"UI.png", []() {}).setPosition({ WinSizeX - 200, WinSizeY - 100 }).AddText(L"적 소환", 50).Get<Button>();

	gameManager->EndWave = [this]() { //웨이브 종료시 함수
		shop_spawnButton->SetInteractive(true); 
		WaveCount->GetComponent<D2DFont>()->SetDialog(L"Wave " + std::to_wstring(gameManager->WaveLevel)); 	
		shop->init();
		if (gameManager->WaveLevel == 3 || gameManager->WaveLevel == 6)
			compensation->SetActive(true);
		else
			showWave->Show();
	}; 
	gameManager->GameClear = []() { Factory().createObj<GameOver>(); };
	ChangeButton();
	shop_spawnButton->SetInteractive(true);
} 

void BattleWorld::ChangeButton()
{
	if (Swap)
	{
		shop_spawnButton->SetListener([this]() { spwaner->StartWave(); ChangeButton(); }); 
		shop_spawnButton->GetComponent<D2DFont>()->SetDialog(L"적소환");
	}
	else
	{
		shop_spawnButton->SetListener([this]() { shop->SetActive(true); shop->Reroll(); ChangeButton(); });
		shop_spawnButton->GetComponent<D2DFont>()->SetDialog(L"타워소환");
	}
	Swap = !Swap;
	shop_spawnButton->SetInteractive(false);
}

void BattleWorld::Update(float deltaTime) 
{
	__super::Update(deltaTime);
	gameManager->Update();	
	if (Swap == false)		
	{
		int count=0;
		for (int i = 0; i < TowerInventory.size(); i++)
		{
			if (TowerInventory[i]->isContain == false)
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

	if (InputSystem::GetInstance()->isKeyDown('K'))
	{
		gameManager->LiveEenmy = 0;
		gameManager->isBattle = true;
	}
}

void BattleWorld::Render(ID2D1HwndRenderTarget* pRenderTarget, float Alpha)
{
	__super::Render(pRenderTarget);
}
