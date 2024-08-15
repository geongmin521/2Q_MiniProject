#include "pch.h"
#include "BattleWorld.h"
#include "Factory.h"
#include "D2DFont.h"
#include "GameManager.h"
#include "TimeSystem.h"
#include "InputSystem.h"

#include "EnemySpawner.h" //�̰� �������־���ϴ� ��üŬ����.. ���丮���� ���� �ѱ������� ������𸣰ڳ�.. 
#include "Button.h"
#include "Image.h"
#include "Map.h"
#include "GameOver.h"
#include "Compensation.h"
#include "GodStore.h"
#include "Shop.h"
#include "ShowWave.h"
#include "Combination.h"
#include "Container.h"
#include "Light.h" // ����Ʈ �׽�Ʈ


BattleWorld::BattleWorld()
{
}

BattleWorld::~BattleWorld()
{
}

void BattleWorld::MakeObject()
{
	Make(Image)(L"afternoon.png").setScale({ 0.75f,0.75f }).setRenderOrder(-100).setPosition(WinHalfSizeXY); //���
	Make(EnemySpawner)();
	Make(Map)();
	MakeUI();
	showWave->Show(); 
	RegisterEvent();
}

void BattleWorld::MakeUI()//�� ���� ���⼭ � ��� �ʿ����� �м��Ѵ�����. ����� ���������ҵ�? ���Ⱑ �̻����� ���� ���ΰ�? �ٸ� �ڵ�� ������?
{
	Make(GodStore)().setPosition({ WinHalfSizeXY }).Get(Objs["GodStore"]);//�������� �̹��� ��ü �ʿ�
	Make(Button)(L"smallBack.png", [this]() { Objs["GodStore"]->SetActive(true); }).setPosition({ 100, WinHalfSizeY });
	Make(Image)(L"UI.png").setPosition({ WinHalfSizeX, 100 }).AddText(L"Wave 1", 40).GetComponent<D2DFont>(WaveCount); //���̺�ī��Ʈ
	Make(Button)(L"smallBack.png",[]() {timeManager->SetTimeScale(0); }).setPosition({ WinSizeX - 400, 200 }); //�ð� ���� ��ư
	Make(Button)(L"smallBack.png",[]() {timeManager->SetTimeScale(1); }).setPosition({ WinSizeX - 300, 200 });
	Make(Button)(L"smallBack.png",[]() {timeManager->SetTimeScale(2); }).setPosition({ WinSizeX - 200, 200 });
	Make(Shop)().setPosition(WinHalfSizeXY).Get<Shop>(shop);  shop->SetOtherUI(Objs["Combination"]);
	Make(ShowWave)().setPosition(WinHalfSizeXY).Get<ShowWave>(showWave); //UI �гε��� �ٽø�Ƶ��ɰŰ��⵵�ϰ�.. 
	Make(Combination)().setPosition (WinHalfSizeXY).Get(Objs["Combination"]);
	Make(Compensation)().setPosition(WinHalfSizeXY).Get(Objs["Compensation"]);
	Make(Button)(L"UI.png", [this]() { Objs["Combination"]->SetActive(true); }).setPosition(WinSizeXYAdd(-600, -100)).AddText(L"���ս�", 50); //���ս�
	Make(GameOver)().setPosition({ WinHalfSizeXY }).Get(Objs["GameOver"]);
	//Make(Light)();
}
void BattleWorld::RegisterEvent()
{
	gameManager->events["EndWave"] = [this]() { //���̺� ����� �Լ�
		shop->GetSwapButton()->SetInteractive(true);
		WaveCount->SetDialog(L"Wave " + std::to_wstring(gameManager->WaveLevel));
		shop->init();
		if (gameManager->WaveLevel == 3 || gameManager->WaveLevel == 6)
			Objs["Compensation"]->SetActive(true);
		else
			showWave->Show();
	};
	gameManager->events["GameOver"] = [this]() {Objs["GameOver"]->SetActive(true);};	
}

void BattleWorld::Update(float deltaTime) 
{
	__super::Update(deltaTime);
	gameManager->Update();	
}

void BattleWorld::Render(ID2D1HwndRenderTarget* pRenderTarget, float Alpha)
{
	__super::Render(pRenderTarget);
}
