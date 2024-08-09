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
	//Fac->CreateImage(L"낮.png", { WinHalfSizeX, WinHalfSizeY }); // 테스트용 배경출력

	//Fac->CreateTower<ArrowTower>(1); //스트링만 넣어주면되나? 
	spwaner = Fac->CreateGameObject<EnemySpawner>();
	Fac->CreateGameObject<Map>(); //결국헤더에 이것에 대한 참조가 있어야하니까.. 팩토리의 장점이 사라지는거같은데.. 아니면
	//팩토리에 일관되게함수를 구성할수가없긴함.. 나중에 정리할수있을까? 
	MakeUI();
	
}

void BattleWorld::MakeUI() //앞에 경로는 다정해져있으니까 위에서 처리하자.. 
{
	Fac->CreateImage(L"UI.png", { WinHalfSizeX, 100 }); //스테이지 -이거는 텍스트박스를 하나더 만들어야할듯. 

	Fac->CreateButton(L"smallBack.png", []() {timeManager->SetTimeScale(0); }, { WinSizeX - 400, 200 }); //일시정시
	Fac->CreateButton(L"smallBack.png", []() {timeManager->SetTimeScale(1); }, { WinSizeX - 300, 200 }); //일시정시
	Fac->CreateButton(L"smallBack.png", []() {timeManager->SetTimeScale(2); }, { WinSizeX - 200, 200 }); //배속 //버튼도 이전에 크기정하는게 필요하지않을까나? 
	Fac->CreateButton(L"UI.png", [this]() { combination->isActive = true; }, { WinSizeX - 400, WinSizeY - 100 }); //조합식 띄우기 

	for (int i = 0; i < 4; i++)
	{
		IconInven.push_back(Fac->CreateGameObject<Container>());
		IconInven[i]->transform->SetRelativeLocation({ 100.0f + i * 150, WinSizeY - 100 });
	}
		

	combination = Fac->CreateGameObject<Combination>(); combination->isActive = false;
	shop = Fac->CreateGameObject<Shop>(); shop->isActive = false; shop->SetOtherUI(IconInven, combination); shop->spawner = spwaner;
	
	showWave = Fac->CreateGameObject<ShowWave>(); showWave->isActive = false;
	Fac->CreateButton(L"UI.png", [this]() { shop->isActive = true; }, { WinSizeX - 200, WinSizeY - 100 }); //타워 소환 -> 상점을띄워주는 객체
	Fac->CreateButton(L"ImageBack.png", [this]() { shop->isActive = true; }, { WinSizeX - 200, WinSizeY - 100 }); //타워 소환 -> 상점을띄워주는 객체

	Fac->CreateGameObject<EnemySpawner>();
	Fac->CreateGameObject<Light>();
}
