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
#include "Image.h"
#include "Map.h"

#include "Light.h" // 라이트 테스트


BattleWorld::BattleWorld()
{
}

BattleWorld::~BattleWorld()
{

}

void BattleWorld::MakeObject() //월드의 좌표같은것들도 csv로 빼야할수도있을듯? 
{
	Factory().createObj<Image>(L"afternoon.png").setPosition(WinHalfSizeXY); // 테스트용 배경출력
	spwaner = Factory().createObj<EnemySpawner>().Get<EnemySpawner>(); 
	Factory().createObj<Map>();
	MakeUI();
	
}

void BattleWorld::MakeUI() //앞에 경로는 다정해져있으니까 위에서 처리하자.. 
{
	Factory().createObj<Image>(L"UI.png").setPosition({ WinHalfSizeX, 100 }).AddText(L"Wave 1", 40);; //wave //웨이브 관리를 일반 이미지로는힘드니까 showwave한테 넘기자. 
	Factory().createObj<Button>(L"smallBack.png",[]() {timeManager->SetTimeScale(0); }).setPosition({ WinSizeX - 400, 200 }); //시간 조절 버튼
	Factory().createObj<Button>(L"smallBack.png",[]() {timeManager->SetTimeScale(1); }).setPosition({ WinSizeX - 300, 200 });
	Factory().createObj<Button>(L"smallBack.png",[]() {timeManager->SetTimeScale(2); }).setPosition({ WinSizeX - 200, 200 });

	for (int i = 0; i < 4; i++)
	{
		IconInven.push_back(Factory().createObj<Container>().setPosition({ 100.0f + i * 150, WinSizeY - 100 }).Get<Container>());
	}
		
	combination = Factory().createObj<Combination>().Get<Combination>();
	shop = Factory().createObj<Shop>().Get<Shop>(); shop->SetOtherUI(IconInven, combination); shop->spawner = spwaner;//상점이 스포너 들고있을필요없음
	showWave = Factory().createObj<ShowWave>().Get<ShowWave>();

	Factory().createObj<Button>(L"UI.png", [this]() { combination->SetActive(true); }).setPosition({ WinSizeX - 600, WinSizeY - 100 }).AddText(L"조합식", 50); //조합표띄우기
	spawnButton = Factory().createObj<Button>(L"UI.png", [this]() { spwaner->StartWave(); spawnButton->isActive = false;  }).
		setPosition({ WinSizeX - 200, WinSizeY - 100 }).AddText(L"적 소환", 50).setActive(false).setRenderOrder(60).Get<Button>(); //적들 생성 버튼
	shopButton = Factory().createObj<Button>(L"UI.png", [this]() { shop->SetActive(true); spawnButton->isActive = true; }).
		setPosition({ WinSizeX - 200, WinSizeY - 100 }).AddText(L"타워소환", 50).Get<Button>(); //타워 소환 -> 상점을띄워주는 객체
}
