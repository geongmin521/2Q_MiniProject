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

#include "Light.h" // ����Ʈ �׽�Ʈ


BattleWorld::BattleWorld()
{
}

BattleWorld::~BattleWorld()
{

}

void BattleWorld::MakeObject() //������ ��ǥ�����͵鵵 csv�� �����Ҽ���������? 
{
	Factory().createObj<Image>(L"afternoon.png").setPosition(WinHalfSizeXY); // �׽�Ʈ�� ������
	spwaner = Factory().createObj<EnemySpawner>().Get<EnemySpawner>(); 
	Factory().createObj<Map>();
	MakeUI();
	
}

void BattleWorld::MakeUI() //�տ� ��δ� �������������ϱ� ������ ó������.. 
{
	Factory().createObj<Image>(L"UI.png").setPosition({ WinHalfSizeX, 100 });
	Factory().createObj<Button>(L"smallBack.png",[]() {timeManager->SetTimeScale(0); }).setPosition({ WinSizeX - 400, 200 });
	Factory().createObj<Button>(L"smallBack.png",[]() {timeManager->SetTimeScale(1); }).setPosition({ WinSizeX - 300, 200 });
	Factory().createObj<Button>(L"smallBack.png",[]() {timeManager->SetTimeScale(2); }).setPosition({ WinSizeX - 200, 200 });
	Factory().createObj<Button>(L"UI.png", [this]() { combination->SetActive(true); }).setPosition({WinSizeX - 400, WinSizeY - 100});

	for (int i = 0; i < 4; i++)
	{
		IconInven.push_back(Factory().createObj<Container>().setPosition({ 100.0f + i * 150, WinSizeY - 100 }).Get<Container>());
	}
		
	combination = Factory().createObj<Combination>().setIsActive(false).Get<Combination>();
	shop = Factory().createObj<Shop>().setIsActive(false).Get<Shop>(); shop->SetOtherUI(IconInven, combination); shop->spawner = spwaner;//������ ������ ��������ʿ����
	showWave = Factory().createObj<ShowWave>().setIsActive(false).Get<ShowWave>();

	Factory().createObj<Button>(L"UI.png", [this]() { combination->SetActive(true); }).setPosition({ WinSizeX - 400, WinSizeY - 100 }); //����ǥ����
	Factory().createObj<Button>(L"ImageBack.png", [this]() { shop->SetActive(true); }).setPosition({WinSizeX - 200, WinSizeY - 100}); //Ÿ�� ��ȯ -> ����������ִ� ��ü
}
