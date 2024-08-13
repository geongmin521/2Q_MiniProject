#include "pch.h"
#include "BattleWorld.h"
#include "Camera.h"
#include "Button.h"
#include "MoveIcon.h"
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

#include "Light.h" // 라이트 테스트


BattleWorld::BattleWorld()
{
}

BattleWorld::~BattleWorld()
{
}

void BattleWorld::MakeObject() //월드의 좌표같은것들도 csv로 빼야할수도있을듯? 
{
	Factory().createObj<Image>(L"afternoon.png").setRenderOrder(-100).setPosition(WinHalfSizeXY); // 테스트용 배경출력 //아이걸.. 맵에서 그리는게 아니라 그냥 이미지로해놨었네.. 
	spwaner = Factory().createObj<EnemySpawner>().Get<EnemySpawner>(); 
	Factory().createObj<Map>();
	MakeUI();

	DataManager::GetInstance().get()->ChoseWave();
	showWave->Show(); 
}

void BattleWorld::MakeUI() //앞에 경로는 다정해져있으니까 위에서 처리하자.. 
{
	WaveCount = Factory().createObj<Image>(L"UI.png").setPosition({ WinHalfSizeX, 100 }).AddText(L"Wave 1", 40).Get<Image>(); //wave //웨이브 관리를 일반 이미지로는힘드니까 showwave한테 넘기자. 
	Factory().createObj<Button>(L"smallBack.png",[]() {timeManager->SetTimeScale(0); }).setPosition({ WinSizeX - 400, 200 }); //시간 조절 버튼
	Factory().createObj<Button>(L"smallBack.png",[]() {timeManager->SetTimeScale(1); }).setPosition({ WinSizeX - 300, 200 });
	Factory().createObj<Button>(L"smallBack.png",[]() {timeManager->SetTimeScale(2); }).setPosition({ WinSizeX - 200, 200 });

	for (int i = 0; i < 4; i++) //타워 인벤
	{
		TowerInventory.push_back(Factory().createObj<Container>().setPosition({ 100.0f + i * 150, WinSizeY - 100 }).Get<Container>());
	}
		
	combination = Factory().createObj<Combination>().Get<Combination>();
	shop = Factory().createObj<Shop>().Get<Shop>(); shop->SetOtherUI(TowerInventory, combination); shop->spawner = spwaner;//상점이 스포너 들고있을필요없음
	showWave = Factory().createObj<ShowWave>().Get<ShowWave>();
	
	Factory().createObj<Button>(L"UI.png", [this]() { combination->SetActive(true); }).setPosition({ WinSizeX - 600, WinSizeY - 100 }).AddText(L"조합식", 50); //조합표띄우기
	shop_spawnButton = Factory().createObj<Button>(L"UI.png", []() {}).setPosition({ WinSizeX - 200, WinSizeY - 100 }).AddText(L"적 소환", 50).Get<Button>();
	//일단 비어놓고.. 함수를 할당해주기.. 
	//gameManager->ShowWave = [this]() { showWave->Show(); }; 
	gameManager->EndWave = [this]() { 
		shop_spawnButton->SetInteractive(true); 
		WaveCount->GetComponent<D2DFont>()->SetDialog(L"Wave " + std::to_wstring(gameManager->WaveLevel)); 
		showWave->Show();
		shop->init();
	}; //웨이브가끝날때 필요한 함수들을 여기다 저장해놓기..
	gameManager->GameClear = []() { Factory().createObj<GameOver>(); }; //싱글톤 init만들어서 초기화를 시켜버려야할듯? 
	ChangeButton();
	shop_spawnButton->SetInteractive(true); //처음에는 일단가능하게
	//gameManager->GameClear();

} 

void BattleWorld::ChangeButton() //여기선 말그대로 기능만 바꿔주고.. 나머지는 람다식으로 들고있는걸로가자... 
{
	if (Swap)
	{
		shop_spawnButton->SetListener([this]() { spwaner->StartWave(); ChangeButton(); }); //본인한테 이거 맡기면안되나? 
		shop_spawnButton->GetComponent<D2DFont>()->SetDialog(L"적소환");
	}
	else
	{
		shop_spawnButton->SetListener([this]() { shop->SetActive(true); ChangeButton(); });
		shop_spawnButton->GetComponent<D2DFont>()->SetDialog(L"타워소환");
	}
	Swap = !Swap;
	shop_spawnButton->SetInteractive(false); //이거 인터렉티브를 설정해줘야하는데.. 이건 게임매니저한테 맡기는게 맞나? 아니면? 월드의 업데이트를 가지고있을까? 그냥? //이거 오브젝트의 업데이트로는 무리일거같은데.. 
}

void BattleWorld::Update(float deltaTime) //이정도로 규모의 게임을 자체엔진으로는 처음만들어보는데 이게 맞는걸까?  
{
	__super::Update(deltaTime);
	gameManager->Update(); //업데이트를 배틀중에만 돌려야할듯? 
	if (Swap == false) //현재 적소환버튼이면서, 비활성화 상태일때. 
	{
		int count=0;
		for (int i = 0; i < TowerInventory.size(); i++)
		{
			if (TowerInventory[i]->isContain == false)
				count++;
		}
		if (count == 4) //전부 비어있으면 활성화
		{
			shop_spawnButton->SetInteractive(true);
		}
		else
		{
			shop_spawnButton->SetInteractive(false); //일단 이렇게 더럽게 짜놓고 나중에 고치자 시간없다
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
