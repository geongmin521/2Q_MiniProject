#include "../D2DEngine/pch.h"
#include "BattleWorld.h"
#include "Camera.h"
#include "ArrowTower.h"
#include "Button.h"
#include "MoveIcon.h"
#include "Factory.h"
#include "Shop.h"
#include "ShowWave.h"
#include "Combination.h"
#include "Container.h"
#include "../D2DEngine/TimeSystem.h"
#include "../D2DEngine/DataManager.h"
#include "../D2DEngine/Transform.h"
#include "EnemySpawner.h"

BattleWorld::BattleWorld()
{

}

BattleWorld::~BattleWorld()
{

}

void BattleWorld::MakeObject() //월드의 좌표같은것들도 csv로 빼야할수도있을듯? 
{
	MakeUI();
	DataManager::GetInstance().get()->CSVReader(L"EnemyData");
}

void BattleWorld::MakeUI() //앞에 경로는 다정해져있으니까 위에서 처리하자.. 
{
	Fac->CreateImage(L"ImageBack.png", { WinHalfSizeX, 100 }); //스테이지 -이거는 텍스트박스를 하나더 만들어야할듯. 
	Fac->CreateButton(L"ImageBack.png", []() {timeManager->SetTimeScale(0); }, { WinSizeX - 400, 200 }); //일시정시
	Fac->CreateButton(L"ImageBack.png", []() {timeManager->SetTimeScale(2); }, { WinSizeX - 200, 200 }); //배속 
	Fac->CreateButton(L"ImageBack.png", [this]() { combination->isActive = true; }, { WinSizeX - 400, WinSizeY - 100 }); //조합식 띄우기 

	for (int i = 0; i < 4; i++)
	{
		IconInven.push_back(Fac->CreateGameObject<Container>());
		IconInven[i]->transform->SetRelativeLocation({ 100.0f + i * 200, WinSizeY - 100 });
	}
		

	combination = Fac->CreateGameObject<Combination>(); combination->isActive = false;
	shop = Fac->CreateGameObject<Shop>(); shop->isActive = false; shop->SetOtherUI(IconInven, combination);
	
	showWave = Fac->CreateGameObject<ShowWave>(); showWave->isActive = false;
	Fac->CreateButton(L"ImageBack.png", [this]() { shop->isActive = true; }, { WinSizeX - 200, WinSizeY - 100 }); //타워 소환 -> 상점을띄워주는 객체

	Fac->CreateTower<ArrowTower>(1); //스트링만 넣어주면되나? 
	Fac->CreateGameObject<EnemySpawner>();
	
}
