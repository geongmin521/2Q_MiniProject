#include "../D2DEngine/pch.h"
#include "BattleWorld.h"

#include "Map.h"
#include "Camera.h"
#include "ArrowTower.h"
#include "Button.h"
#include "MoveIcon.h"
#include "Factory.h"
#include "Shop.h"
#include "ShowWave.h"
#include "Combination.h"
#include "../D2DEngine/TimeSystem.h"

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
}

void BattleWorld::MakeUI() //앞에 경로는 다정해져있으니까 위에서 처리하자.. 
{
	Fac->CreateImage(L"ImageBack.png", { WinHalfSizeX, 100 }); //스테이지 -이거는 텍스트박스를 하나더 만들어야할듯. 
	Fac->CreateButton(L"ImageBack.png", []() {timeManager->SetTimeScale(0); }, { WinSizeX - 400, 200 }); //일시정시
	Fac->CreateButton(L"ImageBack.png", []() {timeManager->SetTimeScale(2); }, { WinSizeX - 200, 200 }); //배속 
	Fac->CreateButton(L"ImageBack.png", [this]() { combination->isActive = true; }, { WinSizeX - 400, WinSizeY - 100 }); //조합식 띄우기 
	//조합식이 얼마나 단순한지 알려줘야하는데.. 상점은 어떻게 뛰우냐.. UI를 그대로 들고있고.. active연결해주자... 
	//웨이브 표시 팝업은 언제 뜨는거지?
	shop = CreateGameObject<Shop>();
	shop->isActive = false;
	combination = CreateGameObject<Combination>();
	combination->isActive = false;
	showWave = CreateGameObject<ShowWave>();
	showWave->isActive = false;
	Fac->CreateButton(L"ImageBack.png", [this]() { shop->isActive = true; }, { WinSizeX - 200, WinSizeY - 100 }); //타워 소환 -> 상점을띄워주는 객체

	
	CreateGameObject<ArrowTower>(); //각월드에 초기 필요한 오브젝트 생성하기
	CreateGameObject<Button>();
	CreateGameObject<MoveIcon>();
	CreateGameObject<EnemySpawner>();
}
