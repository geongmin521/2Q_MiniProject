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

void BattleWorld::MakeObject() //������ ��ǥ�����͵鵵 csv�� �����Ҽ���������? 
{
	MakeUI();
	DataManager::GetInstance().get()->CSVReader(L"EnemyData");
}

void BattleWorld::MakeUI() //�տ� ��δ� �������������ϱ� ������ ó������.. 
{
	Fac->CreateImage(L"ImageBack.png", { WinHalfSizeX, 100 }); //�������� -�̰Ŵ� �ؽ�Ʈ�ڽ��� �ϳ��� �������ҵ�. 
	Fac->CreateButton(L"ImageBack.png", []() {timeManager->SetTimeScale(0); }, { WinSizeX - 400, 200 }); //�Ͻ�����
	Fac->CreateButton(L"ImageBack.png", []() {timeManager->SetTimeScale(2); }, { WinSizeX - 200, 200 }); //��� 
	Fac->CreateButton(L"ImageBack.png", [this]() { combination->isActive = true; }, { WinSizeX - 400, WinSizeY - 100 }); //���ս� ���� 

	for (int i = 0; i < 4; i++)
	{
		IconInven.push_back(Fac->CreateGameObject<Container>());
		IconInven[i]->transform->SetRelativeLocation({ 100.0f + i * 200, WinSizeY - 100 });
	}
		

	combination = Fac->CreateGameObject<Combination>(); combination->isActive = false;
	shop = Fac->CreateGameObject<Shop>(); shop->isActive = false; shop->SetOtherUI(IconInven, combination);
	
	showWave = Fac->CreateGameObject<ShowWave>(); showWave->isActive = false;
	Fac->CreateButton(L"ImageBack.png", [this]() { shop->isActive = true; }, { WinSizeX - 200, WinSizeY - 100 }); //Ÿ�� ��ȯ -> ����������ִ� ��ü

	Fac->CreateTower<ArrowTower>(1); //��Ʈ���� �־��ָ�ǳ�? 
	Fac->CreateGameObject<EnemySpawner>();
	
}
