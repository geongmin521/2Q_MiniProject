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

void BattleWorld::MakeObject() //������ ��ǥ�����͵鵵 csv�� �����Ҽ���������? 
{
	MakeUI();
}

void BattleWorld::MakeUI() //�տ� ��δ� �������������ϱ� ������ ó������.. 
{
	Fac->CreateImage(L"ImageBack.png", { WinHalfSizeX, 100 }); //�������� -�̰Ŵ� �ؽ�Ʈ�ڽ��� �ϳ��� �������ҵ�. 
	Fac->CreateButton(L"ImageBack.png", []() {timeManager->SetTimeScale(0); }, { WinSizeX - 400, 200 }); //�Ͻ�����
	Fac->CreateButton(L"ImageBack.png", []() {timeManager->SetTimeScale(2); }, { WinSizeX - 200, 200 }); //��� 
	Fac->CreateButton(L"ImageBack.png", [this]() { combination->isActive = true; }, { WinSizeX - 400, WinSizeY - 100 }); //���ս� ���� 
	//���ս��� �󸶳� �ܼ����� �˷�����ϴµ�.. ������ ��� �ٿ��.. UI�� �״�� ����ְ�.. active����������... 
	//���̺� ǥ�� �˾��� ���� �ߴ°���?
	shop = CreateGameObject<Shop>();
	shop->isActive = false;
	combination = CreateGameObject<Combination>();
	combination->isActive = false;
	showWave = CreateGameObject<ShowWave>();
	showWave->isActive = false;
	Fac->CreateButton(L"ImageBack.png", [this]() { shop->isActive = true; }, { WinSizeX - 200, WinSizeY - 100 }); //Ÿ�� ��ȯ -> ����������ִ� ��ü

	
	CreateGameObject<ArrowTower>(); //�����忡 �ʱ� �ʿ��� ������Ʈ �����ϱ�
	CreateGameObject<Button>();
	CreateGameObject<MoveIcon>();
	CreateGameObject<EnemySpawner>();
}
