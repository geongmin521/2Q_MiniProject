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

#include "Light.h" // ����Ʈ �׽�Ʈ


BattleWorld::BattleWorld()
{
	
}

BattleWorld::~BattleWorld()
{

}

void BattleWorld::MakeObject() //������ ��ǥ�����͵鵵 csv�� �����Ҽ���������? 
{
	//Fac->CreateImage(L"��.png", { WinHalfSizeX, WinHalfSizeY }); // �׽�Ʈ�� ������

	//Fac->CreateTower<ArrowTower>(1); //��Ʈ���� �־��ָ�ǳ�? 
	spwaner = Fac->CreateGameObject<EnemySpawner>();
	Fac->CreateGameObject<Map>(); //�ᱹ����� �̰Ϳ� ���� ������ �־���ϴϱ�.. ���丮�� ������ ������°Ű�����.. �ƴϸ�
	//���丮�� �ϰ��ǰ��Լ��� �����Ҽ���������.. ���߿� �����Ҽ�������? 
	MakeUI();
	
}

void BattleWorld::MakeUI() //�տ� ��δ� �������������ϱ� ������ ó������.. 
{
	Fac->CreateImage(L"UI.png", { WinHalfSizeX, 100 }); //�������� -�̰Ŵ� �ؽ�Ʈ�ڽ��� �ϳ��� �������ҵ�. 

	Fac->CreateButton(L"smallBack.png", []() {timeManager->SetTimeScale(0); }, { WinSizeX - 400, 200 }); //�Ͻ�����
	Fac->CreateButton(L"smallBack.png", []() {timeManager->SetTimeScale(1); }, { WinSizeX - 300, 200 }); //�Ͻ�����
	Fac->CreateButton(L"smallBack.png", []() {timeManager->SetTimeScale(2); }, { WinSizeX - 200, 200 }); //��� //��ư�� ������ ũ�����ϴ°� �ʿ����������? 
	Fac->CreateButton(L"UI.png", [this]() { combination->isActive = true; }, { WinSizeX - 400, WinSizeY - 100 }); //���ս� ���� 

	for (int i = 0; i < 4; i++)
	{
		IconInven.push_back(Fac->CreateGameObject<Container>());
		IconInven[i]->transform->SetRelativeLocation({ 100.0f + i * 150, WinSizeY - 100 });
	}
		

	combination = Fac->CreateGameObject<Combination>(); combination->isActive = false;
	shop = Fac->CreateGameObject<Shop>(); shop->isActive = false; shop->SetOtherUI(IconInven, combination); shop->spawner = spwaner;
	
	showWave = Fac->CreateGameObject<ShowWave>(); showWave->isActive = false;
	Fac->CreateButton(L"UI.png", [this]() { shop->isActive = true; }, { WinSizeX - 200, WinSizeY - 100 }); //Ÿ�� ��ȯ -> ����������ִ� ��ü
	Fac->CreateButton(L"ImageBack.png", [this]() { shop->isActive = true; }, { WinSizeX - 200, WinSizeY - 100 }); //Ÿ�� ��ȯ -> ����������ִ� ��ü

	Fac->CreateGameObject<EnemySpawner>();
	Fac->CreateGameObject<Light>();
}
