#include "pch.h"
#include "BattleWorld.h"
#include "Factory.h"
#include "D2DFont.h"
#include "GameManager.h"
#include "TimeSystem.h"
#include "InputSystem.h"
#include "Pools.h"

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
#include "Artifact.h"
#include "TowerBase.h"
#include "Music.h"

#include "D2DFontManager.h"

BattleWorld::BattleWorld()
{
	Music::soundManager->GetInstance()->PlayMusic(Music::eSoundList::MainTheme, Music::eSoundChannel::BGM);
}

BattleWorld::~BattleWorld()
{
}

void BattleWorld::MakeObject()
{
	D2DFontManager::GetInstance()->LoadFont(L"..\\Data\\Font\\DNFBitBitv2.ttf", L"Test");
	D2DFontManager::GetInstance()->LoadFont(L"..\\Data\\Font\\Maplestory Bold.ttf", L"Map");

	Make(Image)(L"afternoon.png").setScale({ 0.75f,0.75f }).setRenderOrder(-100).setPosition(WinHalfSizeXY); //ȿ���� ���� ���Ľ�Ƽ ��
	Make(EnemySpawner)();
	Make(Map)();
	MakeUI();
	showWave->Show();
	RegisterEvent();
}

void BattleWorld::MakeUI()//�� ���� ���⼭ � ��� �ʿ����� �м��Ѵ�����. ����� ���������ҵ�? ���Ⱑ �̻����� ���� ���ΰ�? �ٸ� �ڵ�� ������?
{
	Make(GodStore)().setPosition({ WinHalfSizeXY }).Get(Objs["GodStore"]);//�������� �̹��� ��ü �ʿ�
	Make(Button)(L"smallBack.png", [this]() { if (gameManager->isBattle == false) Objs["GodStore"]->SetActive(true); }).setPosition({ 100, WinHalfSizeY }); //�������� ��ư
	Make(Image)(L"UI.png").setPosition({ WinHalfSizeX, 100 }).AddText(L"Wave 1", 40).GetComponent<D2DFont>(WaveCount); //���̺�ī��Ʈ
	Make(Image)(L"UI.png").setPosition({ WinSizeX - 100, 100 }).AddText(L"�žӽ� : 0", 40).GetComponent<D2DFont>(goldText); //������ȭ
	Make(Button)(L"smallBack.png",[]() {timeManager->SetTimeScale(0); }).setPosition({ WinSizeX - 400, 200 }); //�ð� ���� ��ư
	Make(Button)(L"smallBack.png",[]() {timeManager->SetTimeScale(1); }).setPosition({ WinSizeX - 300, 200 });
	Make(Button)(L"smallBack.png",[]() {timeManager->SetTimeScale(2); }).setPosition({ WinSizeX - 200, 200 });
	Make(Shop)().setPosition(WinHalfSizeXY).Get<Shop>(shop);  shop->SetOtherUI(Objs["Combination"]);
	Make(ShowWave)().setPosition({ WinHalfSizeX+1200,WinHalfSizeY}).Get<ShowWave>(showWave); //UI �гε��� �ٽø�Ƶ��ɰŰ��⵵�ϰ�.. 


	Make(Combination)().setPosition (WinHalfSizeXY).Get(Objs["Combination"]);
	Make(Compensation)().setPosition(WinHalfSizeXY).Get(Objs["Compensation"]);
	Make(Button)(L"UI.png", [this]() { Objs["Combination"]->SetActive(true); }).setPosition(WinSizeXYAdd(-600, -100)).AddText(L"���ս�", 50); //���ս�
	Make(GameOver)().setPosition({ WinHalfSizeXY }).Get(Objs["GameOver"]);
	//Make(Light)();
}

void BattleWorld::RegisterEvent()
{
	gameManager->events[Event::EndWave] = [this]() { //���̺� ����� �Լ�
		shop->GetSwapButton()->SetInteractive(true);
		shop->init();
		gameManager->chance = 1;
		shop->ChangeButton(ButtonState::TowerSpawn);
		WaveCount->SetDialog(L"Wave " + std::to_wstring(gameManager->WaveLevel));
		if (gameManager->WaveLevel == 3 || gameManager->WaveLevel == 6)
		{
			Objs["Compensation"]->SetActive(true);
		}
		else
		{
			showWave->Show();
		}
		for (auto& it : m_GameObjects)
		{
			if (it && it->name == "Tower")
			{
				TowerBase* tower = dynamic_cast<TowerBase*>(it);

				if (tower)
				{
					if (tower->curHP <= 0)
					{
						tower->prevHp = tower->towerData.HP;
					}
					tower->curHP = tower->prevHp;
					tower->StatUpdate();
				}
			}
		}

		};
	gameManager->events[Event::GameOverEvent] = [this]() {Objs["GameOver"]->SetActive(true);
	Music::soundManager->StopMusic(Music::eSoundChannel::BGM); };
	//Music::soundManager->PlayMusic(Music::eSoundList::GameOver, Music::eSoundChannel::BGM); };
	gameManager->events[Event::UseGold] = [this]() { goldText->SetDialog(L"�žӽ�:" + std::to_wstring(gameManager->GetGold())); };
	gameManager->events[Event::Reset] = [this]() { Pools::GetInstance().get()->reset(); };//�� �̱����̸鼭 ���������� �����͸� ����ִ¾ְ��ֳ�? 
} 

void BattleWorld::Update(float deltaTime)
{
	__super::Update(deltaTime);
	gameManager->Update();	
	goldText->SetDialog(L"�žӽ� :" + std::to_wstring(gameManager->GetGold())); // �ǽð� ������ ���� �ϴ� �߰��س���
}

void BattleWorld::Render(ID2D1HwndRenderTarget* pRenderTarget, float Alpha)
{
	__super::Render(pRenderTarget);
}
